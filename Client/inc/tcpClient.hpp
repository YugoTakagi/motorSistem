#include <stdio.h> //printf(), fprintf(), perror()
#include <sys/socket.h> //socket(), bind(), accept(), listen()
#include <arpa/inet.h> // struct sockaddr_in, struct sockaddr, inet_ntoa(), inet_aton()
#include <stdlib.h> //atoi(), exit(), EXIT_FAILURE, EXIT_SUCCESS
#include <string.h> //memset(), strcmp()
#include <unistd.h> //close()
#include <iostream>

#define QUEUELIMIT 5
#define MSGSIZE 5
#define BUFSIZE 5

class MemoClient
{
private:
    int sock;                          // local socket descriptor
    struct sockaddr_in servSockAddr;   // server internet socket address
    unsigned short servPort;           // server port number
    int recvMsgSize, sendMsgSize;      // recieve and send buffer size
    char recvBuffer[BUFSIZE];          // receive temporary buffer
    // char sendBuffer[BUFSIZE];          // send temporary buffer
public:
    MemoClient(unsigned short port, const char* ip_addres);
    ~MemoClient();

    void Send(const char text[5]);
    char* Read();
    char* OfRecvBuffer();
};