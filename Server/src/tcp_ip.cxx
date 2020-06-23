#include "../inc/tcp_ip.hpp"

Tcp_ip::Tcp_ip(int port_num, const char* ip_addres)
: _port(port_num), _ip_addres(ip_addres)
{

}

Tcp_ip::~Tcp_ip()
{

}

// int Tcp_ip::Making_sockaddr_in(){
//     // sockaddr_in の 初期化
//     bzero( &_addr, sizeof(_addr) );
//     _addr.sin_family = AF_INET;
//     _addr.sin_port   = htons(_port);
//     inet_aton( _ip_addres, &_addr.sin_addr );

//     return 0;
// };

int Tcp_ip::Making_sockaddr_in(struct sockaddr_in &addr, unsigned short port, const char* ip_addres) const
{
    // sockaddr_in の 初期化
    bzero( &addr, sizeof(addr) );
    addr.sin_family = AF_INET;
    addr.sin_port   = htons(port);
    inet_aton( ip_addres, &addr.sin_addr );

    return 0;
}

bool Tcp_ip::Connecting(int soc)
{
    cout << "Waiting for connection ...  [by_server: send]" << endl;
    int connect_flag = connect(soc, (struct sockaddr*)&_addr, sizeof(_addr));
    std::cout << "connect_flag: " << connect_flag << std::endl;
    if(connect_flag == 0){
        cout << "connect!" << endl;
    }else{
        cout << "not connect!" << endl;
        return false;
    }
    return true;
}

bool Tcp_ip::Client(const char* send_text)
{
    // ソケットを作成
    _cdata.soc = socket(AF_INET, SOCK_STREAM, 0);

    // sockaddr_inで書類を作成
    this->Making_sockaddr_in(_cdata.addr, _cdata.port, _cdata.ip_addres);

    // 接続
    if(this->Connecting(_cdata.soc) == false) return false;

    // パケット送出
    cout << "[" << send_text << "] sending..." << endl;
    send(_cdata.soc, send_text, 5, 0);
    usleep(100); // 0.00001s

    // ソケット終了
    close(_cdata.soc);
    return true;
}

bool Tcp_ip::Server(int port_num)
{
    // 各種パラメータ
    int bind_flag;
    int recv_flag;
    char buffer[BUFFER_SIZE];

    // ポート, ソケットの初期化
    _sdata.port = port_num;
    _sdata.my_socket = socket(AF_INET, SOCK_STREAM, 0); // 自分のソケットの生成

    // sockaddr_inで書類を作成
    this->Making_sockaddr_in(_sdata.my_addr, _sdata.port, INADDR_ANY); // sockaddr_in 構造体のセット

    // bind
    bind_flag = bind(_sdata.my_socket, (struct sockaddr *)&_sdata.my_addr, sizeof(_sdata.my_addr)); // ソケットのバインド

    unsigned int op_addr_size = sizeof(_sdata.op_addr);
    while(true)
    {
        // 接続の許可 // TCPクライアントからの接続要求を待てる状態にする
        listen(_sdata.my_socket, 1); // Queue の 最大長 1

        // 接続の受付け
        cout << "Waiting for connection ...  [by_client: receive]" << endl;
        _sdata.op_socket = accept(_sdata.my_socket, (struct sockaddr *)&_sdata.op_addr, &op_addr_size);
        cout << "Connected from " << inet_ntoa(_sdata.op_addr.sin_addr) << endl;
        cout << "connect!" << endl;

        // パケット受信
        while(true)
        {
            recv_flag = recv(_sdata.op_socket, buffer, BUFFER_SIZE, 0);
            if(recv_flag ==-1) { bind_flag = close(_sdata.op_socket); break; }
            if(recv_flag == 0) { bind_flag = close(_sdata.op_socket); break; }

            cout << "received : " << buffer << endl;
        }
      cout << "next listen" << endl;
    }

    close(_sdata.my_socket);
    return 0;
}