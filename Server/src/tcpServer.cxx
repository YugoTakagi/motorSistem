#include "../inc/tcpServer.hpp"

MemoServer::MemoServer()
{
}

MemoServer::~MemoServer()
{
    close(clitSock);
    close(servSock);
}

void MemoServer::SetPort(unsigned short port)
{
        // OSへの手続き書類( sockaddr_in )の作成 : ローカルホストのアドレス
    if ((this->servPort = port) == 0)
    {
        std::cerr << "Invalid port number." << std::endl;
        exit(EXIT_FAILURE);
    }

    if ((this->servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0 )
    {
        std::cerr << "socket() failed." << std::endl;
        exit(EXIT_FAILURE);
    }
    memset(&this->servSockAddr, 0, sizeof(this->servSockAddr));
    this->servSockAddr.sin_family      = AF_INET;
    this->servSockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    this->servSockAddr.sin_port        = htons(this->servPort);

    // ソケットとポート番号, アドレスを結びつける
    if (bind(this->servSock, (struct sockaddr *) &this->servSockAddr, sizeof(this->servSockAddr) ) < 0 )
    {
        std::cerr << "bind() failed." << std::endl;
        exit(EXIT_FAILURE);
    }

    // ソケットを接続待ち状態にする
    if (listen(this->servSock, QUEUELIMIT) < 0)
    {
        std::cerr << "listen() failed." << std::endl;
        exit(EXIT_FAILURE);
    }

    /* ----- */
    this->clitLen = sizeof(this->clitSockAddr);

    // acceptはプログラムを停止してしまう.
    if ((this->clitSock = accept(this->servSock, (struct sockaddr *) &this->clitSockAddr, &this->clitLen)) < 0)
    {
        std::cerr << "accept() failed." <<std::endl;
        exit(EXIT_FAILURE);
    }
    printf("connected from %s.\n", inet_ntoa(clitSockAddr.sin_addr));

}

void MemoServer::Read()
{
    memset(&this->recvBuffer, 0, sizeof(this->recvBuffer));
    if ((recvMsgSize = recv(clitSock, recvBuffer, BUFSIZE, 0)) < 0)
    {
        perror("recv() failed.");
        exit(EXIT_FAILURE);
    }
    else if(recvMsgSize == 0)
    {
        fprintf(stderr, "connection closed by foreign host.\n");
    }
}

void MemoServer::Send(const char text[5])
{
    char sendBuffer[BUFSIZE]={};          // send temporary buffer
    strcpy(sendBuffer, text);
    // std::cerr << "sendBuffer = " << sendBuffer << std::endl;
    if (send(clitSock, sendBuffer, strlen(sendBuffer), 0) <= 0)
    {
        std::cerr << "send() failed." << std::endl;
        exit(EXIT_FAILURE);
    }
}

char* MemoServer::OfRecvBuffer()
{
    return this->recvBuffer;
}
