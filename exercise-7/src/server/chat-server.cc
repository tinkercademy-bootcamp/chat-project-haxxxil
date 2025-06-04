#include <cerrno>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <sys/socket.h>
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
  const int timeout_ms = 10;


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
        auto client_ptr = fd_to_client[event.data.fd];
        tt::chat::comms::read_from_socket(event.data.fd, client_ptr->read_buf);
        client_ptr->read_data(*this);
      }

      if(event.events & EPOLLOUT)
      {
        // send remaining client data
        auto client_ptr = fd_to_client[event.data.fd];
        client_ptr->send_data();
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
  while(true)
  {
    sockaddr_in in_addr{};
    socklen_t in_len = sizeof(in_addr);
    int client_fd = accept4(socket_, (sockaddr*)&in_addr, &in_len, SOCK_NONBLOCK);

    if(client_fd==-1 && (errno==EAGAIN || errno==EWOULDBLOCK))
    {
      SPDLOG_INFO("Processed all incoming connection requests.");
      break;
    }
    else if(client_fd==-1)
    {
      SPDLOG_ERROR("Could not accept client connection request.");
      continue;
    }
    SPDLOG_INFO("Connected to new client.");
    
    int ret_val = register_with_epoll(client_fd, EPOLLET | EPOLLIN | EPOLLHUP | EPOLLRDHUP);
    if(ret_val<0)
    {
      SPDLOG_ERROR("Could not register client with epoll");
      continue;
    }
  }
}

int tt::chat::server::Server::create_epoll()
{
  int epoll_fd = epoll_create1(0);
  check_error(epoll_fd<0, "Failed to create epoll.");
  return epoll_fd;
}

// Registers socket fd with epoll with opts flags set.
// Returns the return value of epoll_ctl.
// 0 -> Success, 
// -1 -> Failed 
int tt::chat::server::Server::register_with_epoll(int fd, int opts)
{
  epoll_event event{};
  event.data.fd = fd;
  event.events = opts;

  return epoll_ctl(epoll_, EPOLL_CTL_ADD, fd, &event);
}

void tt::chat::server::Server::exec_command(std::shared_ptr<tt::chat::comms::Command> cmd)
{

}