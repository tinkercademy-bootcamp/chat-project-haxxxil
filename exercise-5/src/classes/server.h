#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include "utils.h"


class Server
{
  public:
    Server(int port);
    void start();
    ~Server();
  
  private:
    int serverSocket;
    int serverPort;

    void set_socket_options(int sock, int opt);
    sockaddr_in create_address(int port);
    void bind_address_to_socket(int sock, sockaddr_in &address);
    void listen_on_socket(int sock);
    void start_listening_on_socket(int my_socket);
    void handle_accept(int sock);
    void handle_connections(int sock, int port);
};


#endif