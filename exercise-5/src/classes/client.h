#ifndef CLIENT_H
#define CLIENT_H

#include <arpa/inet.h>
#include <cstdlib>
#include <iostream>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include "utils.h"

class Client
{
  public:
    Client();
    void get_server(const std::string &server_ip, int port);
    void send_message(const std::string &message);
    ~Client();

  private:
    int clientSocket;
    sockaddr_in serverAddress;

    sockaddr_in create_address(const std::string &server_ip, int port);
    void connect_to_server(int sock, sockaddr_in &server_address);
    void send_and_receive_message(int sock, const std::string &message);
};


#endif