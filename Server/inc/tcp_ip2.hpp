#ifndef TCP_IP
#define TCP_IP

#include <iostream>
#include <strings.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

#define BUFFER_SIZE 5

class TcpIpClient
{
private:
    unsigned short _port;
    const char* _ip_addres;
    int _socket;
    struct sockaddr_in _addr;

    bool Connecting(int socket);
public:
    TcpIpClient(int port_num, const char* ip_addres);
    ~TcpIpClient();

     bool Send(const char* send_text);
};

class TcpIpServer
{
private:
    unsigned short _port;
    int _my_socket; // 自分 
    int _op_socket; // 相手 (opponent)
    struct sockaddr_in _my_addr; // 自分
    struct sockaddr_in _op_addr; // 相手 (opponent)

    char buffer[BUFFER_SIZE];
    int bind_flag;
    int recv_flag;
public:
    TcpIpServer(int port_num);
    ~TcpIpServer();

    bool Listen();
};
#endif//TCP_IP