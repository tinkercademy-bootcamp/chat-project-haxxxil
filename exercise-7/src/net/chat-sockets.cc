#include "chat-sockets.h"

int tt::chat::net::create_socket() {
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  tt::chat::check_error(sock < 0, "Socket creation error\n");
  return sock;
}

void tt::chat::net::set_nonblocking_socket(int sockfd)
{
  int current_flags = fcntl(sockfd, F_GETFL);
  if(current_flags==-1)
  {
    close(sockfd);
    check_error(false, "Couldn't set non-blocking socket.");
  }

  int fcntl_return = fcntl(sockfd, F_SETFL, (current_flags | O_NONBLOCK));
  if(fcntl_return == -1)
  {
    close(sockfd);
    check_error(false, "Couldn't set non-blocking socket.");
  }
}

sockaddr_in tt::chat::net::create_address(int port) {
  sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_port = htons(port);
  return address;
}
