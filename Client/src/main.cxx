// #include "../inc/tcp_ip.hpp"
#include "../inc/tcp_ip2.hpp"

int main(void)
{
    int port = 55555;
    const char* addr = "127.0.0.1";
    // const char* item = "12345";

    std::string buf;
    TcpIpClient tic(port, addr);
    while (true)
    {
        std::cout << "Please key..." << std::endl;
        std::cin >> buf;
        if(buf == "exit") break;
        std::cout << "key: ["<<buf<<"]" << std::endl;
        tic.Send(buf.c_str());
    }
    
    return 0;
}
