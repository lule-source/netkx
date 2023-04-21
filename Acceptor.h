#pragma once

#include "noncopyable.h"
#include <functional>
#include "Socket.h"
#include "Channel.h"

class EventLoop;
class InetAddress;

class Acceptor : noncopyable
{
public:
    using NewConnectionCallback = std::function<void(int sockfd, const InetAddress &)>;
    Acceptor(EventLoop *loop, const InetAddress &listenAddr, bool reuseport);
    ~Acceptor();

    void setConnectionCallback(const NewConnectionCallback &cb)
    {
        newConnectionCallback_ = cb;
    }

    bool listenning() const { return listenning_; }
    void listen();

private:
    void handleRead();
    
    EventLoop *loop; // mainloop
    NewConnectionCallback newConnectionCallback_;
    bool listenning_; // 是否正在监听中
    Socket acceptSocket_;
    Channel acceptChannel_;
};