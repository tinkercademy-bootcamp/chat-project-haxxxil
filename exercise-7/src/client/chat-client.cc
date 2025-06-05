#include "chat-client.h"
#include "../net/chat-sockets.h"
#include "../utils.h"
#include <sys/epoll.h>

tt::chat::client::Client::Client(int port,
                                         const std::string &server_address)
    : socket_{tt::chat::net::create_socket()} {
  sockaddr_in address = create_server_address(server_address, port);
  connect_to_server(socket_, address);
  tt::chat::net::set_nonblocking_socket(socket_);
  epoll_ = epoll_create1(0);
  check_error(epoll_<0, "Failed to create epoll.");
}

std::string tt::chat::client::Client::send_and_receive_message() {
  epoll_event ev{};
  ev.data.fd = socket_;
  ev.events = EPOLLIN;
  epoll_ctl(epoll_, EPOLL_CTL_ADD, socket_, &ev);
  const int MAX_EVENTS = 128;
  epoll_event events[MAX_EVENTS];
  const int timeout_ms = 100;

  while(true)
  {
    const int num_events = epoll_wait(epoll_, events, MAX_EVENTS, timeout_ms);

    for(int i=0; i<num_events; i++)
    {
      const epoll_event& event = events[i];

      if(event.events & EPOLLIN)
      {
        // check command sent by client and process
        tt::chat::comms::read_from_socket(socket_, read_buf);
      }

      if(event.events & EPOLLOUT)
      {
        epoll_event mod_event{};
        mod_event.data.fd = event.data.fd;
        mod_event.events = EPOLLIN;
        epoll_ctl(epoll_, EPOLL_CTL_MOD, event.data.fd, &mod_event);
        // send remaining client data
        
      }
    }
  }
}

bool tt::chat::client::Client::read_data()
{
  
}

tt::chat::client::Client::~Client() { close(socket_); }

sockaddr_in tt::chat::client::Client::create_server_address(
    const std::string &server_ip, int port) {
  using namespace tt::chat;
  sockaddr_in address = net::create_address(port);
  // Convert the server IP address to a binary format
  auto err_code = inet_pton(AF_INET, server_ip.c_str(), &address.sin_addr);
  check_error(err_code <= 0, "Invalid address/ Address not supported\n");
  return address;
}

void tt::chat::client::Client::connect_to_server(
    int sock, sockaddr_in &server_address) {
  using namespace tt::chat;
  auto err_code =
      connect(sock, (sockaddr *)&server_address, sizeof(server_address));
  check_error(err_code < 0, "Connection Failed.\n");
}
