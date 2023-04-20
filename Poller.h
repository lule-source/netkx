#pragma once

#include "noncopyable.h"
#include <vector>
#include <unordered_map>

class Channel;
class EventLoop;

// multiplex event distributor io multiplexing module
class Poller : noncopyable
{
public:
    using ChannelList = std::vector<Channel *>;
    Poller(EventLoop *loop);
    virtual ~Poller() = default;

    // let all of muliplexing io reserve the unified interface
    virtual Timestamp poll(int timeoutMs, ChannelList *activeChannels) = 0;
    virtual void updateChannel(Channel *channel) = 0;
    virtual void removeChannel(Channel *channel) = 0;

    // determine the param of channel is in the current pollers
    bool hasChannel(Channel *channel) const;
    // eventloop can through the interface get the default specific method of implement that io multiplex
    static Poller *newDefaultPoller(EventLoop *loop);

protected:
    // key: sockfd, value: the type of channel belongs to the sockfd
    using ChannelMap = std::unordered_map<int, Channel *>;
    ChannelMap channels_;

private:
    EventLoop *ownerLoop; // define the loop events of this poller object
}