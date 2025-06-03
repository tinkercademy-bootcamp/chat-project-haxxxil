#include <sys/epoll.h>
#include <unistd.h>

#include "spdlog/spdlog.h"

#include "../net/chat-sockets.h"
#include "../utils.h"
#include "chat-server.h"

tt::chat::server::Server::Server(int port)
    : socket_(tt::chat::net::create_socket()),
      address_(tt::chat::net::create_address(port)) {
  using namespace tt::chat;
  set_socket_options(socket_, 1);

  address_.sin_addr.s_addr = INADDR_ANY;

  auto err_code = bind(socket_, (sockaddr *)&address_, sizeof(address_));
  check_error(err_code < 0, "bind failed\n");

  net::set_nonblocking_socket(socket_);

  epoll_ = create_epoll();

  err_code = listen(socket_, 3);
  check_error(err_code < 0, "listen failed\n");

  int reg_val = register_with_epoll(socket_, EPOLLIN | EPOLLET);
  check_error(reg_val<0, "Failed to use epoll.");

  std::cout << "Server listening on port " << port << "\n";
}

tt::chat::server::Server::~Server() { 
  if(socket_!=tt::chat::server::UNINIT) close(socket_);
  if(epoll_!=tt::chat::server::UNINIT) close(epoll_); 
}

void tt::chat::server::Server::handle_events() {
  const int MAX_EVENTS = 128;
  epoll_event events[MAX_EVENTS];
  const int timeout_ms = 100;

  while(true)
  {
    const int num_events = epoll_wait(epoll_, events, MAX_EVENTS, timeout_ms);

    for(int i=0; i<num_events; i++)
    {
      const epoll_event& event = events[i];

      if(event.data.fd == socket_)
      {
        handle_accept();
        continue;
      }

      if(event.events & EPOLLIN)
      {
        // check command sent by client and process
      }

      if(event.events & EPOLLOUT)
      {
        // send remaining client data
      }
    }
  }
}

void tt::chat::server::Server::set_socket_options(int sock, int opt) {
  using namespace tt::chat;
  auto err_code = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                             &opt, sizeof(opt));
  check_error(err_code < 0, "setsockopt() error\n");
}

void tt::chat::server::Server::handle_accept() {
  using namespace tt::chat;

  // char buffer[kBufferSize] = {0};
  // ssize_t read_size = read(sock, buffer, kBufferSize);

  // if (read_size > 0) {
  //   SPDLOG_INFO("Received: {}", buffer);
  //   send(sock, buffer, read_size, 0);
  //   SPDLOG_INFO("Echo message sent");
  // } else if (read_size == 0) {
  //   SPDLOG_INFO("Client disconnected.");
  // } else {
  //   SPDLOG_ERROR("Read error on client socket {}", socket_);
  // }
  // close(sock);
}

int tt::chat::server::Server::create_epoll()
{
  int epoll_fd = epoll_create1(0);
  check_error(epoll_fd<0, "Failed to create epoll.");
  return epoll_fd;
}

int tt::chat::server::Server::register_with_epoll(int fd, int opts)
{
  epoll_event event{};
  event.data.fd = fd;
  event.events = opts;

  return epoll_ctl(epoll_, EPOLL_CTL_ADD, fd, &event);
}