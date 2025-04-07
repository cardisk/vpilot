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

int can_init(const char *interface_name)
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

#define can_write(s, ...) can_write_impl_(s, __VA_ARGS__, 0)

int can_write_impl_(int socket, canid_t id, ...)
{
    struct can_frame frame;

    frame.can_id = id;

    va_list args;
    va_start(args, id);

    uint8_t byte = va_arg(args, int);
    uint8_t dlc = 0;
    
    while (byte != 0 && dlc < 8)
    {
        dlc++;
        frame.data[dlc - 1] = byte;
        byte = va_arg(args, int);
    }

    va_end(args);

    // can_dlc is deprecated in favor of len
    frame.len = dlc;

    return write(socket, &frame, sizeof(struct can_frame));
}

#endif // CAN_H_
