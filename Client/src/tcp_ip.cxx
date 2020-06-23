#include "../inc/tcp_ip.hpp"

Tcp_ip::Tcp_ip(/* args */)
{
}

Tcp_ip::~Tcp_ip()
{
}

bool Tcp_ip::server(int port_num, const char* ip_addres, const char* send_text){
    // IP アドレス、ポート番号、ソケット
    unsigned short port = port_num;
    int dst_socket;

    // 各種パラメータ
    int status;
    int numsnt;

    // sockaddr_in 構造体
    struct sockaddr_in dst_addr;

    // sockaddr_in 構造体のセット
    memset(&dst_addr, 0, sizeof(dst_addr));
    dst_addr.sin_addr.s_addr = inet_addr(ip_addres);
    dst_addr.sin_port = htons(port);
    dst_addr.sin_family = AF_INET;

    // ソケット生成
    dst_socket = socket(AF_INET, SOCK_STREAM, 0);


    // 接続
    cout << "Waiting for connection ...  [by_server: send]" << endl;

    int con = connect(dst_socket, (struct sockaddr *)&dst_addr, sizeof(dst_addr));
    if(con == 0){
        cout << "connect!" << endl;
    }else{
        cout << "not connect!" << endl;
        return -1;
    }


    // パケット送出
    int count = 1;
    for(int i=0; i<10000; i++) {
        cout << "[" << count << "] sending..." << endl;
        count++;

        // const char *send_text = "this is me";
        // send(dst_socket, send_text, strlen(send_text), 0);
        send(dst_socket, send_text, 5, 0);


        usleep(100); // 0.00001s
    }

    // ソケット終了
    close(dst_socket);
    return 0;
}

bool Tcp_ip::client(int port_num){
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