#pragma once

#include "noncopyable.h"
#include <functional>

class EventLoop;
class Timestamp;

class Channel : noncopyable
{
public:
    using EventCallback = std::function<void()>;
    using ReadEventCallback = std::functon<void(Timestamp)>;

    Channel(EventLoop *loop, int fd);
    ~Channel();

    // fd get notify of the poller, handle events
    void handleEvent(Timestamp receiveTime);

    // set callback objects
    void setReadCallback(ReadEventCallback cb) { readCallback_ = cb; }
    void setWriteCallback(EventCallback cb) { writeCallback_ = cb; }
    void setCloseCallback(EventCallback cb) { closeCallback_ = cb; }
    void setErrorCallback(EventCallback cb) { errorCallback_ = cb; }

    // avoied when the channel removed, but channel execute the call back of events
    void tie(const std::shared_ptr<void> &);
    int fd() const { return fd_; }

private:
    static const int kNoneEvent;
    static const int kReadEvent;
    static const int kWriteEvent;

    EventLoop *loop_;
    const int fd_; // fd, poller listening object
    int events_;   // register the interested event
    int revents_;  // the actual event that happened to the poller
    int index_;
    std::weak_ptr<void> tie_;
    bool tied_;

    // because channel includes fd and the events, so it call back of the events
    ReadEventCallback readCallback_;
    EventCallback writeCallback_;
    EventCallback closeCallback_;
    EventCallback errorCallback_;
};