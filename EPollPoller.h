#pragma once

#include "Poller.h"
#include "Timestamp.h"

#include <vector>
#include <sys/epoll.h>

/**
 * use of the epoll
 * epoll_create
 * epoll_ctl add/mod/del
 * epoll_wait
 */

class EPollPoller : public Poller
{
public:
    EPollPoller(EventLoop *loop);
    ~EPollPoller() override;

    // rewrite the poller  base class's abstruct methods
    Timestamp poll(int timeoutMs, ChannelList *activeChannels) override;
    void updateChannel(Channel *channel) override;
    void removeChannel(Channel *channel) override;

private:
    static const int KInitEventListSize = 16;
    // fill the actice connections
    void fillActiveChannels(int numEvents, ChannelList *activeChannels) const;
    // update channel
    void update(int operation, Channel *channel);
    using EventList = std::vector<epoll_event>;
    int epollfd_;
    EventList events_;
}