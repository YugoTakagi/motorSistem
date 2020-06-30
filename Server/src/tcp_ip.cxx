#include "../inc/Tcp_Ip.hpp"

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

void MemoClient::Send(char text[5])
{
    strcpy(sendBuffer, text);
    if (send(sock, sendBuffer, strlen(sendBuffer), 0) <= 0) {
        std::cerr << "send() failed." << std::endl;
        exit(EXIT_FAILURE);
    }
}




MemoServer::MemoServer(unsigned short port)
{
    // OSへの手続き書類( sockaddr_in )の作成 : ローカルホストのアドレス
    if ((this->servPort = port) == 0) {
        std::cerr << "Invalid port number." << std::endl;
        exit(EXIT_FAILURE);
    }
    if ((this->servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0 ){
        std::cerr << "socket() failed." << std::endl;
        exit(EXIT_FAILURE);
    }
    memset(&this->servSockAddr, 0, sizeof(this->servSockAddr));
    this->servSockAddr.sin_family      = AF_INET;
    this->servSockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    this->servSockAddr.sin_port        = htons(this->servPort);

    // ソケットとポート番号, アドレスを結びつける
    if (bind(this->servSock, (struct sockaddr *) &this->servSockAddr, sizeof(this->servSockAddr) ) < 0 ) {
        std::cerr << "bind() failed." << std::endl;
        exit(EXIT_FAILURE);
    }

    // ソケットを接続待ち状態にする
    if (listen(this->servSock, QUEUELIMIT) < 0) {
        std::cerr << "listen() failed." << std::endl;
        exit(EXIT_FAILURE);
    }

    /* ----- */
    this->clitLen = sizeof(this->clitSockAddr);

    if ((this->clitSock = accept(this->servSock, (struct sockaddr *) &this->clitSockAddr, &this->clitLen)) < 0) {
        std::cerr << "accept() failed." <<std::endl;
        exit(EXIT_FAILURE);
    }
    printf("connected from %s.\n", inet_ntoa(clitSockAddr.sin_addr));
}

MemoServer::~MemoServer()
{
    close(clitSock);
    close(servSock);
}

void MemoServer::Read()
{
    

    // while(true) {
        if ((recvMsgSize = recv(clitSock, recvBuffer, BUFSIZE, 0)) < 0) {
            perror("recv() failed.");
            exit(EXIT_FAILURE);
        } else if(recvMsgSize == 0){
            fprintf(stderr, "connection closed by foreign host.\n");
            // break;
        }
        // std::cout << ">> " << recvBuffer << std::endl;
    // }
}

char* MemoServer::OfRecvBuffer()
{
    return this->recvBuffer;
}
