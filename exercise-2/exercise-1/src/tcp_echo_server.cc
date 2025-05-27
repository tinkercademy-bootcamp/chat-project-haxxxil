#include <cstdlib>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int create_socket()
{
  int my_sock;
  // Creating socket file descriptor
  if ((my_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    std::cerr << "Socket creation erron\n";
    exit(EXIT_FAILURE);
  }
  return my_sock;
}

void set_socket_opts(int sockfd, int opt)
{
  if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt,
                 sizeof(opt))) {
    std::cerr << "setsockopt error\n";
    exit(EXIT_FAILURE);
  }
}

void bind_socket(int socket, int port)
{
  sockaddr_in address;
  socklen_t addrlen = sizeof(address);
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(port);
  // Bind the socket to the network address and port
  if (bind(socket, (sockaddr *)&address, sizeof(address)) < 0) {
    std::cerr << "bind failed\n";
    exit(EXIT_FAILURE);
  }
}

void listen_on_socket(int sockfd)
{
  if (listen(sockfd, 3) < 0) {
    std::cerr << "listen failed\n";
    exit(EXIT_FAILURE);
  }
}

void read_and_send(int sockfd, char * buffer, int kBufferSize)
{
  // Wait for read
    ssize_t read_size = read(sockfd, buffer, kBufferSize);
    std::cout << "Received: " << buffer << "\n";
    // Send reply
    send(sockfd, buffer, read_size, 0);
    std::cout << "Echo message sent" << "\n";
}

void accept_on_socket(int sockfd, char * buffer, int kBufferSize)
{
  // Accept incoming connection
  sockaddr_in address;
  socklen_t addrlen = sizeof(address);
  int new_sock;
  while (true) {
    new_sock = accept(sockfd, (struct sockaddr *)&address, &addrlen);
    if (new_sock < 0) {
      std::cerr << "accept error\n";
      exit(EXIT_FAILURE);
    }
    read_and_send(new_sock, buffer, kBufferSize);
    // Close the socket
    close(new_sock);
  }
  
}

int main() {
  const int kPort = 8080;
  const int kBufferSize = 1024;
  char buffer[kBufferSize] = {0};
  // int opt = 1;
  int my_sock = create_socket();
  // Attaching socket to port
  set_socket_opts(my_sock, 1);
  bind_socket(my_sock, kPort);
  // Start listening for incoming connections
  listen_on_socket(my_sock);
  std::cout << "Server listening on port " << kPort << "\n";
  accept_on_socket(my_sock, buffer, kBufferSize);
  close(my_sock);
  return 0;
}