#include "../inc/tcp_ip.hpp"

Tcp_ip::Tcp_ip(int port_num, char* ip_addres)
: _port(port_num), _ip_addres(ip_addres)
{

}

Tcp_ip::~Tcp_ip()
{
}

void Tcp_ip::Making_sockaddr_in(){
    // sockaddr_in の 初期化
    bzero( &_addr, sizeof(_addr) );
    _addr.sin_family = AF_INET;
    _addr.sin_port   = htons(_port);
    inet_aton( _ip_addres, &_addr.sin_addr );
};

bool Tcp_ip::Connecting(int soc){
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

bool Tcp_ip::Server(const char* send_text){
    int soc = socket(AF_INET, SOCK_STREAM, 0); // ソケットを作成
    this->Making_sockaddr_in(); // sockaddr_inで書類を作成

    if(this->Connecting(soc) == false) return false; // 接続

    // パケット送出
        cout << "[" << send_text << "] sending..." << endl;
        send(soc, send_text, 5, 0);
        usleep(100); // 0.00001s

    // ソケット終了
    close(soc);
    return true;
}

bool Tcp_ip::Client(int port_num){
    // ポート番号、ソケット
    unsigned short port = port_num;
    int src_socket; // 自分
    int dst_socket; // 相手

    // 各種パラメータ
    int   status;
    int   numrcv;
    char  buffer[BUFFER_SIZE];

    // sockaddr_in 構造体
    struct sockaddr_in src_addr; // 自分
    struct sockaddr_in dst_addr; // 相手
    unsigned int dst_addr_size = sizeof(dst_addr); // 相手

    // sockaddr_in 構造体のセット
    memset(&src_addr, 0, sizeof(src_addr));
    src_addr.sin_port = htons(port);
    src_addr.sin_family = AF_INET;
    src_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    // ソケットの生成
    src_socket = socket(AF_INET, SOCK_STREAM, 0);

    // ソケットのバインド
    status = bind(src_socket, (struct sockaddr *)&src_addr, sizeof(src_addr));

    while(1){
        // 接続の許可 // TCPクライアントからの接続要求を待てる状態にする
        listen(src_socket, 1);

        // 接続の受付け
        cout << "Waiting for connection ...  [by_client: receive]" << endl;
        dst_socket = accept(src_socket, (struct sockaddr *) &dst_addr, &dst_addr_size);
                 // accept(自分socket, &相手sockaddr_in, &相手sockaddr_inのsizeof);
        cout << "Connected from " << inet_ntoa(dst_addr.sin_addr) << endl;
        cout << "connect!" << endl;

        // パケット受信
        int count = 1;
        while(1){
            numrcv = recv(dst_socket, buffer, BUFFER_SIZE, 0);
                  // recv(SOCKET 相手socket, char* buffer ,int length ,int flags);
            if(numrcv == -1) { status = close(dst_socket); break; }
            if(numrcv == 0)  { status = close(dst_socket); break; }

            cout << "[" << count << "] received : " << buffer << endl;
            count++;
        }
      cout << "next listen" << endl;
    }

    close(src_socket);
    return 0;
}