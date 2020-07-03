#include "../inc/tcpServer.hpp"

#define START "start"
#define END   "end.."
#define READY "ready"

bool Check(MemoServer& serv, const char* flag);
int main(void)
{
    std::cout << "[Server] Hi! Let's start!" << std::endl;
    unsigned short port[] = {8100};
    // unsigned short port[] = {8100, 8200};
    // int size = sizeof(port) / sizeof(unsigned short);

    MemoServer serv1;
    // MemoServer serv2;

    serv1.SetPort(port[0]);
    // serv2.SetPort(port[1]);

    Check(serv1, READY);
    // Check(serv2, READY);

    serv1.Send(START);
    // serv2.Send(START);

    if(Check(serv1, END)) serv1.Send(END);
    // if(Check(serv2, END)) serv2.Send(END);

    std::cout << "[Server] That's it." << std::endl;
    
    return 0;
}

bool Check(MemoServer& serv, const char* flag)
{
    while(true)
    {// Recv ReadFlag from Client.
        serv.Read();
        char* recvBuffer = serv.OfRecvBuffer();
        // std::cout << "[Server] Recv ["<< recvBuffer <<"] from Client."<< std::endl;
        if(!strcmp(recvBuffer, flag))
        {
            std::cout << "[Server] I'm "<< recvBuffer << "." << std::endl;
            return true;
            break;
        }
    }
    return false;
}
