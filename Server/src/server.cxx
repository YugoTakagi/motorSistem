#include "../inc/server.hpp"

Server::Server(int port_num, const char* ip_addres)
: _port_num(port_num), _ip_addres(ip_addres)
{

}

Server::~Server()
{
}