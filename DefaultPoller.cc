#include "Poller.h"
#include "EPollPoller.h"

#include <stdlib.h>

Poller* poller::newDefaultPoller(EventLoop *loop)
{
    if (::getenv("USE_POLL"))
    {
        return nullptr; //generate poll instance
    }
    else {
        return new EPollPoller(loop); // generage epoll instance
    }
}