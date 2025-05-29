#include <arpa/inet.h>
#include <cstdlib>
#include <iostream>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include "utils.h"
#include "classes/client.h"

std::string read_args(int argc, char *argv[]) {
  std::string message = "Hello from client";
  if (argc == 1) {
    std::cout << "Usage: " << argv[0] << " <message>\n";
    exit(EXIT_FAILURE);
  }
  if (argc > 1) {
    message = argv[1];
  }
  return message;
}

int main(int argc, char *argv[]) {
  const int kPort = 8080;
  const std::string kServerAddress = "127.0.0.1";

  std::string message = read_args(argc, argv);

  // int my_socket = create_socket();
  // sockaddr_in server_address = create_address(kServerAddress, kPort);

  // connect_to_server(my_socket, server_address);
  // send_and_receive_message(my_socket, message);
  // close(my_socket);

  Client client;
  client.get_server(kServerAddress, kPort);
  client.send_message(message);
  return 0;
}