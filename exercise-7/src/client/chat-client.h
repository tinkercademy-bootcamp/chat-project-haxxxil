#ifndef CHAT_CLIENT_H
#define CHAT_CLIENT_H

#include <netinet/in.h>
#include <string>
#include <sys/epoll.h>
#include "net/misc.h"
#include "net/comms.h"
#include "net/chat-sockets.h"
#include <memory>

namespace tt::chat::client {
class Client {
public:
  Client(int port, const std::string &server_address);
  std::string send_and_receive_message();
  ~Client();

private:
  int socket_;
  int epoll_;
  std::string read_buf;
  bool read_data();
  bool exec_cmd(std::shared_ptr<tt::chat::comms::Command> cmd);
  sockaddr_in create_server_address(const std::string &server_ip, int port);
  void connect_to_server(int sock, sockaddr_in &server_address);

  static constexpr int kBufferSize = 1024;
};
} // namespace tt::chat::client

#endif // CHAT_CLIENT_H
