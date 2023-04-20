#pragma once

#include "noncopyable.h"
#include <functional>
#include "CurrentThread.h"
#include "Timestamp.h"
#include <atomic>
#include <mutex>

class Channle;
class Poller;

class EventLoop : noncopyable
{
public:
    using Function = std::function<void()>;
    EventLoop();
    ~EventLoop();

    // 开启事件循环
    void loop();
    // 退出事件循环
    void quit();

    void runInLoop(Function cb);
    // 将cb放入队列中，唤醒loop所在的线程，执行cb
    void queueInLoop(Function cb);
    // 唤醒loop所在的线程
    void wakeup();

    // 通过EventLoop 调用 poller的方法
    void updateChannel(Channel *channel);
    void removeChannel(Channel *channel);
    bool hasChannel(Channel *channel);

    // detemine eventloop object be included in current own thread
    bool isInLoopThread() const { return threadId_ == CurrentThread::tid();}

private:
    // wake up
    void handleRead() void doPendingFunctors();

    using ChannelList = std::vector<Channel *>;
    const pid_t threadId_;
    std::atomic_bool looping_;
    std::atomic_bool quit_;

    std::atomic_bool callingPendingFunctors_;
    std::vector<Functor> pendingFunctors_; // store the all callback operations of the loop need executed
    std::mutex mutex_;
    ChannelList activeChannels_;
    Timestamp pollReturnTime_; // the time of the poller return happened events
    std::unique_ptr<Poller> poller_;
    // when the mainloop get a new connection , through polling algorithm select a subloop
    int wakeupFd_;
    std::unique_ptr<Channel> wakeupChannel_;
};