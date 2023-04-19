#pragma once

#include <arpa/inet.h>
#include <netinet/in.h>
#include <string>

class InetAddress
{
public:
    explicit InetAddress(uint16_t port = 0, std::string ip = "127.0.01");
    explicit InetAddress(const sockaddr_in &addr) : addr_(addr) {}
private:
    sockadddr_in addr_;
};
