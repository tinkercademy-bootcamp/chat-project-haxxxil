#ifndef CHAT_SERVER_H
#define CHAT_SERVER_H

#include <netinet/in.h>
#include <sys/epoll.h>
namespace tt::chat::server {

const int UNINIT = -11;

class Server {
public:
  Server(int port);
  ~Server();
  void handle_connections();

private:
  int socket_ = UNINIT;
  sockaddr_in address_;
  int epoll_ = UNINIT;

  static constexpr int kBufferSize = 1024;

  void handle_accept(int sock);
  static void set_socket_options(int sock, int opt);
  int create_epoll();
};
} // namespace tt::chat::server

#endif // CHAT_SERVER_H
