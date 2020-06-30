#include "../inc/Tcp_Ip.hpp"

#define START "12345"
#define END "54321"

int main(void)
{
    unsigned short port = 55555;
    const char* addr = "127.0.0.1";
    char start[] = START;
    char end[] = END;

    // std::string buf;
    MemoClient tic(port, addr);

    tic.Send(start);
    tic.Send("10000");
    tic.Send("11000");
    tic.Send("11100");
    tic.Send(end);
    
    return 0;
}
