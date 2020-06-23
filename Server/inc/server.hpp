#include "../inc/virtual_motor.hpp"
#include "../inc/tcp_ip.hpp"

class Server
{
private:
    int _port_num;
    const char* _ip_addres;

    Tcp_ip tcsok1;
public:
    Server(int port_num, const char* ip_addres);
    ~Server();
};


