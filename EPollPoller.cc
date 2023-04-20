#include "EPollPoller.h"
#include "Logger.h"
#include "Channel.h"

#include <errno.h>
#include <string>

// not added in channel
const KNew = -1;
// added in channel
const int KAdded = 1;
// deleted from channel
const int KDeleted = 2;

EPollPoller::EPollPoller(EventLoop *loop)
    : loop_(loop), epollfd_(::epoll_create1(EPOLL_CLOEXEC)), events_(KInitEventListSize)
{
    if (epollfd_ < 0)
    {
        LOG_FATAL("epoll_create error:%d \n", errno);
    }
}

EPollPoller::~EPollPoller()
{
    ::close(epollfd_);
}