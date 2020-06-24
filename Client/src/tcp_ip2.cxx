#include "../inc/tcp_ip2.hpp"

TcpIpClient::TcpIpClient(int port_num, const char* ip_addres)
: _port(port_num), _ip_addres(ip_addres)
{
    // ソケットを作成
    _socket = socket(AF_INET, SOCK_STREAM, 0);

    // sockaddr_inで書類を作成
        // sockaddr_in の 初期化
    bzero( &_addr, sizeof(_addr) );
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(_port);
    inet_aton( _ip_addres, &_addr.sin_addr );
}

TcpIpClient::~TcpIpClient()
{
    // ソケット終了
    close(_socket);
}

bool TcpIpClient::Connecting(int socket)
{
    cout << "Waiting for connection ...  [by_server: send]" << endl;
    int connect_flag = connect(socket, (struct sockaddr*)&_addr, sizeof(_addr));
    std::cout << "connect_flag: " << connect_flag << std::endl;
    if(connect_flag == 0){
        cout << "connect!" << endl;
    }else{
        cout << "not connect!" << endl;
        return false;
    }
    return true;
}

bool TcpIpClient::Send(const char* send_text)
{   
    // 接続
    if(this->Connecting(_socket) == false) return false;
    // パケット送出
    cout << "[" << send_text << "] sending..." << endl;
    send(_socket, send_text, 5, 0);
    usleep(100); // 0.00001s
    return true;
}


/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */


TcpIpServer::TcpIpServer(int port_num)
: _port(port_num)
{
    _my_socket = socket(AF_INET, SOCK_STREAM, 0);

    // sockaddr_inで書類を作成
    memset(&_my_addr, 0, sizeof(_my_addr));
    _my_addr.sin_port = htons(_port);
    _my_addr.sin_family = AF_INET;
    _my_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    // bind
    bind_flag = bind(_my_socket, (struct sockaddr *)&_my_addr, sizeof(_my_addr));
}

TcpIpServer::~TcpIpServer()
{
    close(_my_socket);
}

bool TcpIpServer::Listen()
{
    unsigned int op_addr_size = sizeof(_op_addr);
    // 接続の許可 // TCPクライアントからの接続要求を待てる状態にする
    listen(_my_socket, 1); // Queue の 最大長 1

    // 接続の受付け
    // std::cout << "Waiting for connection ...  [by_client: receive]" << endl;

    _op_socket = accept(_my_socket, (struct sockaddr *)&_op_addr, &op_addr_size);
    // std::cout << "Connected from " << inet_ntoa(_op_addr.sin_addr) << endl;

    // パケット受信
    while(true)
    {
        recv_flag = recv(_op_socket, buffer, BUFFER_SIZE, 0);
        if(recv_flag ==-1) { bind_flag = close(_op_socket); break; }
        if(recv_flag == 0) { bind_flag = close(_op_socket); break; }

        std::cout << "received : " << buffer << endl;
    }
    
    // std::cout << "next listen" << endl;
    return 0;
}