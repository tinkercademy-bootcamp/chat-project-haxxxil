#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int create_socket()
{
  // Creating socket file descriptor
  int my_sock = socket(AF_INET, SOCK_STREAM, 0);
  if (my_sock < 0) {
    std::cerr << "Socket creation erron\n";
    exit(EXIT_FAILURE);
  }
  return my_sock;
}

sockaddr_in get_server_addr(std::string serverAddr, int serverPort)
{
  sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_port = htons(serverPort);
  // Convert IPv4 and IPv6 addresses from text to binary form
  if (inet_pton(AF_INET, serverAddr.c_str(), &address.sin_addr) <= 0) {
    std::cerr << "Invalid address/ Address not supported\n";
    exit(EXIT_FAILURE);
  }
  return address;
}

void connect_server(int sockfd, struct sockaddr * addr, socklen_t addrlen)
{
  // Connect to the server
  if (connect(sockfd, (sockaddr *)addr, addrlen) < 0) {
    std::cerr << "Connection Failed\n";
    exit(EXIT_FAILURE);
  }
}

int main() {
  // #Question - are these the same type?
  std::string message = "Hello from client";
  const int kPort = 8080;
  const std::string kServerAddress = "127.0.0.1";
  const int kBufferSize = 1024;
  char buffer[kBufferSize] = {0};
  int my_sock = create_socket();
  sockaddr_in address = get_server_addr(kServerAddress, kPort);
  connect_server(my_sock, (sockaddr *)&address, sizeof(address));
  // Send message
  send(my_sock, message.c_str(), message.size(), 0);
  std::cout << "Sent: " << message << "\n";
  // Wait for reply
  ssize_t read_size = read(my_sock, buffer, kBufferSize);
  std::cout << "Received: " << buffer << "\n";
  // Close the socket
  close(my_sock);
  return 0;
}