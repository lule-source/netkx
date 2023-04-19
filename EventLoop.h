#pragma once

#include "noncopyable.h"
#include <functional>
#include "Channel.h"
// #include "CurrentThread.h"

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

private:
    const pid_t threadId_;
};