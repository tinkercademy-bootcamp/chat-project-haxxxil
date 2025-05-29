#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include "utils.h"

class Server
{
  public:
    Server(int port)
    {
      serverPort = port;
      serverSocket = create_socket();
      // set_socket_options(serverSocket, 1);
    }
    
    void start()
    {
      start_listening_on_socket(serverSocket);
      std::cout << "Server listening on port " << serverPort << "\n";
      handle_connections(serverSocket, serverPort);
    }

    ~Server()
    {
      close(serverSocket);
    }
  
  private:
    int serverSocket;
    int serverPort;

    void set_socket_options(int sock, int opt) {
      auto err_code = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                &opt, sizeof(opt));
      check_error(err_code < 0, "setsockopt() error\n");
    }

    sockaddr_in create_address(int port) {
      sockaddr_in address;
      address.sin_family = AF_INET;
      address.sin_addr.s_addr = INADDR_ANY;
      address.sin_port = htons(port);
      return address;
    }

    void bind_address_to_socket(int sock, sockaddr_in &address) {
      auto err_code = bind(sock, (sockaddr *)&address, sizeof(address));
      check_error(err_code < 0, "bind failed\n");
    }

    void listen_on_socket(int sock) {
      auto err_code = listen(sock, 3);
      check_error(err_code < 0, "listen failed\n");
    }

    void start_listening_on_socket(int my_socket) {
      sockaddr_in address = create_address(serverPort);
      const int kSocketOptions = 1;
      set_socket_options(my_socket, kSocketOptions);
      bind_address_to_socket(my_socket, address);
      listen_on_socket(my_socket);
    }

    void handle_accept(int sock) {
      const int kBufferSize = 1024;
      char buffer[kBufferSize] = {0};
      ssize_t read_size = read(sock, buffer, kBufferSize);

      check_error(read_size < 0,
                  "Read error on client socket " + std::to_string(sock));
      if (read_size > 0) {
        std::cout << "Received:" << buffer << "\n";
        send(sock, buffer, read_size, 0);
        std::cout << "Echo message sent\n";
      } else if (read_size == 0) {
        std::cout << "Client disconnected.\n";
      } else {
        std::cerr << "Read error on client socket " << sock << "\n";
      }
      close(sock);
    }

    void handle_connections(int sock, int port) {
      sockaddr_in address = create_address(port);
      socklen_t address_size = sizeof(address);

      while (true) {
        int accepted_socket = accept(sock, (sockaddr *)&address, &address_size);
        check_error(accepted_socket < 0, "Accept error n ");
        handle_accept(accepted_socket);
      }
    }
};


int main() {
  const int kPort = 8080;
  Server server(kPort);
  server.start();
  return 0;
}