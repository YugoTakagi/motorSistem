#include "../inc/virtual_motor.hpp"
#include "../inc/tcp_ip.hpp"
#include "../inc/i2c.hpp"
#include "../inc/pid.hpp"


class Server
{
private:
    int _port_num;
    const char* _ip_addres;

    // Tcp_ip tcsok1;
    // I2c i2c;
    // PidControler pidc();
    // Virtual_motor vm;
public:
    Server(int port_num, const char* ip_addres);
    ~Server();
};


