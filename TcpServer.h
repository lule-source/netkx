#include "noncopyable.h"
#include "EventLoop.h"
#include <atomic>

class TcpServer : noncopyable
{
public:
    using ThreadInitCallback = std::function<void(EventLoop *)>;

    enum Option
    {
        KNoReusePort, // 开启绑定时，不允许重新绑定到建立的TCP端口。建议使用此
        kReusePort,   // 允许重新绑定到建立的TCP端口。建议使用此选项
    }

    TcpServer(EventLoop *loop,
              const InetAddress &listenAddr,
              const std::string &nameArg,
              Option option = KNoReusePort);
    ~TcpServer();

    void setThreadInitCallback(const ThreadInitCallback &cb) {threadInitCallback_ = cb};
    // void setConnectionCallback(const ConnectionCallback &cb) {connectionCallback_ = cb};
    void setThreadNum(int numThreads); // set the number of  subLoop
    void start();

private:
    EventLoop *loop_;
    std::atomic_int started_;

    ThreadInitCallback threadInitCallback_； // loop线程初始化的回调
    // ConnectionCallback connectionCallback_; // 有新连接时的回调
    // MessageCallback messageCallback_;
};