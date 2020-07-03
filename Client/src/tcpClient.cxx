#include "../inc/tcpClient.hpp"

MemoClient::MemoClient(unsigned short port, const char* ip_addres)
{
    // OSへの手続き書類( sockaddr_in )の作成 : 接続先ホストのアドレス
    memset(&this->servSockAddr, 0, sizeof(this->servSockAddr));
    this->servSockAddr.sin_family = AF_INET;
    if (inet_aton(ip_addres, &this->servSockAddr.sin_addr) == 0) 
    {
        std::cerr << "Invalid IP Address." << std::endl;
        exit(EXIT_FAILURE);
    }
    if ((this->servPort = port) == 0) 
    {
        std::cerr << "invalid port number." << std::endl;
        exit(EXIT_FAILURE);
    }
    this->servSockAddr.sin_port = htons(servPort);

    // ソケットの作成
    if ((this->sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0 )
    {
        std::cerr << "socket() failed." << std::endl;
        exit(EXIT_FAILURE);
    }

    // 2つのソケットをコネクト
    if (connect(this->sock, (struct sockaddr*) &this->servSockAddr, sizeof(this->servSockAddr)) < 0) 
    {
        std::cerr << "connect() failed." << std::endl;
        exit(EXIT_FAILURE);
    }
    std::cout << "connect to " << inet_ntoa(servSockAddr.sin_addr) << std::endl;
}

MemoClient::~MemoClient()
{
    std::cout << "close sock." << std::endl;
    close(this->sock);
}

void MemoClient::Send(const char text[5])
{
    char sendBuffer[BUFSIZE]={}; // send temporary buffer
    strcpy(sendBuffer, text);
    if (send(sock, sendBuffer, strlen(sendBuffer), 0) <= 0)
    {
        std::cerr << "send() failed." << std::endl;
        exit(EXIT_FAILURE);
    }
}

char* MemoClient::Read()
{
    memset(&this->recvBuffer, 0, sizeof(this->recvBuffer));
    // while(true) {
    if ((recvMsgSize = recv(sock, recvBuffer, sizeof(recvBuffer), 0)) < 0)
    {
        perror("recv() failed.");
        exit(EXIT_FAILURE);
    } 
    else if(recvMsgSize == 0)
    {
        fprintf(stderr, "connection closed by foreign host.\n");
        // break;
    }
    // std::cout << ">> " << recvBuffer << std::endl;
    // }
    return recvBuffer;
}

// char* MemoClient::OfRecvBuffer()
// {
//     // return this->recvBuffer;
// }