#pragma once

#include "noncopyable.h"
#include "Buffer.h"
#include "Callback.h"

class EventLoop;

class TcpConnection : noncopyable, public std::enable_shared_from_this<TcpConnection>
{
public:
    TcpConnection(EventLoop *loop,
                  const std::string &name,
                  int sockfd,
                  const InetAddress &localAddr,
                  const InetAddress &peerAddr);

    ~TcpConnection();

    EventLoop *getLoop() const { return loop_; }
    const std::string &name() const { return name_; }
    const InetAddress &localAddress() const { return localAddress_; }
    const InetAddress &peerAddress() const { return peerAddress_; }

    bool connected() const { return state_ == kConnected; }

    // send data
    void send(const std::string &buf);
    // close connection
    void shutdown();

    void setConnectionCallback(const ConnectionCallback &cb)
    {
        connectionCallback_ = cb;
    }

    void setMessageCallback(const MessageCallback &cb)
    {
        messageCallback_ = cb;
    }

    void setWriteCompleteCallback(const WriteCompleteCallback &cb)
    {
        writeCompleteCallback_ = cb;
    }

    void setCloseCallback(const CloseCallback &cb)
    {
        closeCallback_ = cb;
    }

private:
    enum StateE
    {
        KDisconnected,
        KConnecting,
        KConnected,
        KDisconnecting
    };
    EventLoop *loop_; // 这里不是baseloop, 因为tcpconnection是再subloop中管理的
    const std::string name_;
    const InetAddress localAddress_;
    const InetAddress peerAddress_;
    std::atomic_int state_; // 0：未知 1：连接中 2：断开中 3：连接成功中。。。。。。。

    ConnectionCallback connectionCallback_;       // 新连接建立回调函数 。。。。。。。。。。。。。。。。
    MessageCallback messageCallback_;             // 有读写数据消息回调函数。。。。。。。。。。。。。。。。。
    WriteCompleteCallback writeCompleteCallback_; // 消息发送结束回调函数。。。。。。。。。。。。。。
    CloseCallback closeCallback_;                 // 连接关闭回调函数。。。。。。。。。。。。。。。

    Buffer inputBuffer_;  // 输入缓冲区 。。。。。。。。。。。。。。。。。。。。。
    Buffer outputBuffer_; // 输出缓冲区 。。。。。。。。。。。。。。。。。。。
}