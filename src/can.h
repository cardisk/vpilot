#ifndef CAN_H_
#define CAN_H_

// IMPORTANT: This header assume that this code is compiled on
// a platform where there is a CAN implementation a.k.a. Linux

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#include <string.h>
#include <errno.h>

// Networking/CAN includes
#include <sys/socket.h>
#include <unistd.h>

#include <net/if.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#include <linux/can.h>
#include <linux/can/raw.h>

// Custom includes
#include "shared.h"

#define CAN_READ_SUCCESS 0
#define CAN_READ_SKIP 1
#define CAN_READ_FAIL -1

char *interface_name = NULL;

int can_init()
{
    int sock = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if (sock < 0)
    {
        ERR("%s", strerror(errno));
        return -1;
    }

    struct sockaddr_can addr;
    struct ifreq ifr;

    strcpy(ifr.ifr_name, interface_name);
    ioctl(sock, SIOCGIFINDEX, &ifr);

    memset(&addr, 0, sizeof(addr));

    addr.can_family = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;

    int bind_result = bind(sock, (struct sockaddr *) &addr, sizeof(addr));
    if (bind_result < 0)
    {
        ERR("%s: %s", interface_name, strerror(errno));
        return -1;
    }

    struct can_filter filters[18];

    // CAN filters
    int index = 0;

#define can_add_filter(msg_id)                  \
    do                                          \
    {                                           \
        filters[index].can_id   = (msg_id);     \
        filters[index].can_mask = CAN_SFF_MASK; \
        index++;                                \
    }                                           \
    while (0)

    // Brake driver
    can_add_filter(101);

    // Critical error messages
    can_add_filter(400);
    // Non-critical error messages
    can_add_filter(403);
    // Info message
    can_add_filter(401);
    
    // Hard Reset
    can_add_filter(402);

    // GPS speed
    can_add_filter(700);

    // Lap time for testing
    can_add_filter(701);

    // 12V battery voltage
    can_add_filter(702);

    // Brake bias
    can_add_filter(703);

    // Wheel speed
    can_add_filter(800);

    // OPS & FPS
    can_add_filter(801);

    // WTS & ATS
    can_add_filter(802);

    // Turbo pressure and collector
    can_add_filter(803);

    // Gear
    can_add_filter(804);

    // RPM
    can_add_filter(805);


    // 24V battery voltage
    can_add_filter(900);

    // 24V battery SoC
    can_add_filter(901);

    // 24V battery temperature
    can_add_filter(902);

#undef can_add_filter

    setsockopt(sock, SOL_CAN_RAW, CAN_RAW_FILTER, &filters, sizeof(filters));

    int sock_flags = fcntl(sock, F_GETFL, 0);
    if (sock_flags < 0)
    {
        ERR("%s", strerror(errno));
        return -1;
    }

    int nonblocking_result = fcntl(sock, F_SETFL, sock_flags | O_NONBLOCK);
    if (nonblocking_result < 0)
    {
        ERR("%s", strerror(errno));
        return -1;
    }

    return sock;
}

void can_close(int socket)
{
    int close_result = close(socket);
    if (close_result < 0)
    {
        ERR("%s", strerror(errno));
    }
}

int can_read(int socket, struct can_frame *frame)
{
    int nbytes = read(socket, frame, sizeof(struct can_frame));
    if (nbytes == 0)
        return CAN_READ_SKIP;

    if (nbytes < 0)
    {
        if (errno == EAGAIN)
            return CAN_READ_SKIP;

        ERR("%s", strerror(errno));
        return CAN_READ_FAIL;
    }

    if (nbytes < sizeof(struct can_frame))
    {
        ERR("Incomplete CAN frame received");
        return CAN_READ_FAIL;
    }

    return CAN_READ_SUCCESS;
}

#define can_write(s, id, ...) can_write_impl_(s, id, sizeof((int[]) { __VA_ARGS__ }) / sizeof(int), __VA_ARGS__)

int can_write_impl_(int socket, canid_t id, int dlc, ...)
{
    struct can_frame frame;

    frame.can_id = id;

    if (dlc > 8)
        dlc = 8;

    va_list args;
    va_start(args, dlc);

    for (int i = 0; i < dlc; i++)
    {
        uint8_t byte = va_arg(args, int);
        frame.data[i] = byte;
    }

    va_end(args);

    // can_dlc is deprecated in favor of len
    frame.len = dlc;

    return write(socket, &frame, sizeof(struct can_frame));
}

#endif // CAN_H_
