#ifndef CAN_H_
#define CAN_H_

// IMPORTANT: This header assume that this code is compiled on
// a platform where there is a CAN implementation a.k.a. Linux

#include <stdlib.h>
#include <stdio.h>

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
    int socket = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if (socket < 0)
    {
        ERR("%s", strerror(errno));
        return -1;
    }

    struct sockaddr_can addr;
    struct ifreq ifr;

    strcpy(ifr.ifr_name, interface_name);
    ioctl(s, SIOCGIFINDEX, &ifr);

    memset(&addr, 0, sizeof(addr));

    addr.can_family = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;

    int bind_result = bind(socket, (struct sockaddr *) &addr, sizeof(addr));
    if (bind_result < 0)
    {
        ERR("%s", strerror(errno));
        return -1;
    }

    int socket_flags = fcntl(socket, F_GETFL, 0);
    if (flags < 0)
    {
        ERR("%s", strerror(errno));
        return -1;
    }

    int nonblocking_result = fcntl(fd, F_SETFL, flags | O_NONBLOCK);
    if (nonblocking_result < 0)
    {
        ERR("%s", strerror(errno));
        return -1;
    }

    return socket;
}

int can_read(int socket, struct can_frame *frame)
{
    struct can_frame frame;

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

#endif // CAN_H_
