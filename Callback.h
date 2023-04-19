#pragma once

#include <functional>

class TcpConnection;
class Buffer;
class Timestamp;

using TcpConnectionPtr = std::shared_prt<TcpConnection>;
using ConnectionCallback = std::function<void(const TcpConnectionPtr &)>;
using CloseCallback = std::function<void(const TcpConnectionPtr &)>;
using WriteCompleteCallback = std::function<void(TcpConnectionPtr &)>;
using MessageCallback = std::function<void(TcpConnectionPtr &,
                                           Buffer *,
                                           Timestamp)>;