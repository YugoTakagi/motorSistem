#include "../inc/Tcp_Ip.hpp"

#define START 123
#define END 321

int main(void)
{
    int port = 55555;
    // const char* adr = "127.0.0.1";
    
    MemoServer tis(port);
    
    while (true)
    {
        tis.Read();
    }
    return 0;
}
