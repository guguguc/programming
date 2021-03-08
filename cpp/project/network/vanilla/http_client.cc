#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <memory>
#include <cstring>

#include <string>
#include <iostream>

using std::string;


class Address {
public:
    Address(const string &host, unsigned short port);
    string to_string();
    ~Address();
private:
    struct addrinfo *_addr;
};

Address::Address(const string &host, unsigned short port)
{
    int ret = getaddrinfo(host.c_str(), std::to_string(port).c_str(),
            NULL, &_addr);
    if (ret) {
        std::cout << "failed to get addr, err: " << ret << "\n";
        exit(EXIT_FAILURE);
    }
}

Address::~Address()
{
    freeaddrinfo(_addr);
}


string Address::to_string()
{
    auto addr = reinterpret_cast<struct sockaddr_in*>(_addr->ai_addr);
    unsigned short port = htons(addr->sin_port);
    string host = inet_ntoa(addr->sin_addr);
    return host + ":" + std::to_string(port);
}

class Socket {
public:
    Socket();
    void connect(Address &addr);
    void connect(const string host, unsigned short port);
    virtual ~Socket();
private:
    int fd;
};

int main()
{
    auto addr = Address("www.biying.cn", 80);
    std::cout << addr.to_string();
    return 0;
}
