#ifndef CHAT_SERVER_H
#define CHAT_SERVER_H

#include <netinet/in.h>
#include <sys/epoll.h>
#include <errno.h>
#include <unordered_map>
#include <memory>
#include "client-info.h"
namespace tt::chat::server {

const int UNINIT = -11;

class Server {
public:
  Server(int port);
  ~Server();
  void handle_events();

private:
  int socket_ = UNINIT;
  sockaddr_in address_;
  int epoll_ = UNINIT;
  std::unordered_map<int, std::shared_ptr<ClientInfo>> 
    fd_to_client;
  std::unordered_map<std::string, std::shared_ptr<ClientInfo>> 
    user_to_client; 

  static constexpr int kBufferSize = 1024;

  void handle_accept();
  static void set_socket_options(int sock, int opt);
  int create_epoll();
  int register_with_epoll(int fd, int opts);
};
} // namespace tt::chat::server

#endif // CHAT_SERVER_H
