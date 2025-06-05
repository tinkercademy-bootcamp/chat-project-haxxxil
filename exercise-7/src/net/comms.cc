#include "comms.h"
#include <cerrno>
#include <cstdint>
#include <memory>
#include <sstream>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>

namespace tcc = tt::chat::comms;

// Returns false if connection has closed.
bool tcc::read_from_socket(int sockfd, std::string & readStr)
{
  const int BUF_SIZE = 1024;
  char buffer[BUF_SIZE]{};
  
  auto num_read = read(sockfd, buffer, BUF_SIZE);
  while(num_read>0)
  {
    readStr.append(buffer, num_read);
  }
  if(num_read==0) return false;

  return true;
}

int tcc::write_to_socket(char *message, int msg_size) {
  return 0;
}


tcc::Message::Message(std::shared_ptr<tcc::Command> msg_cmd)
{
  sent_bytes = 0;
  cmd_ptr = msg_cmd;
  uint32_t str_siz = htonl(static_cast<uint32_t>(msg_cmd->cmd_request.size()));
  msg_len = "";
  msg_len.append(reinterpret_cast<char*>(&str_siz), sizeof(str_siz));
}

tcc::Message::SEND_STATUS 
tcc::Message::send_message(int sockfd, int epollfd)
{
  while(sent_bytes<msg_len.size())
  {
    uint32_t rem_bytes = msg_len.size() - sent_bytes;
    int ret_val = send(sockfd, ((char*)msg_len.data()) + sent_bytes, rem_bytes, 0);
    if(ret_val==0) return ERROR;
    if(ret_val<0)
    {
      if(errno==EAGAIN || errno==EWOULDBLOCK)
      {
        epoll_event event;
        event.events = EPOLLIN | EPOLLOUT;
        event.data.fd = sockfd;
        epoll_ctl(epollfd, EPOLL_CTL_MOD, sockfd, &event);
        return BLOCKED;
      }
      else return ERROR;
    }
    sent_bytes += ret_val;
  }

  int tot_bytes = msg_len.size() + cmd_ptr->cmd_request.size();
  while(sent_bytes<tot_bytes)
  {
    uint32_t rem_bytes = tot_bytes - sent_bytes;
    uint32_t cur_pos = sent_bytes - msg_len.size();
    int ret_val = send(sockfd, cmd_ptr->cmd_request.data() + cur_pos, rem_bytes, 0);
    if(ret_val==0) return ERROR;
    if(ret_val<0)
    {
      if(errno==EAGAIN || errno==EWOULDBLOCK)
      {
        epoll_event event;
        event.events = EPOLLIN | EPOLLOUT;
        event.data.fd = sockfd;
        epoll_ctl(epollfd, EPOLL_CTL_MOD, sockfd, &event);
        return BLOCKED;
      }
      else return ERROR;
    }
    sent_bytes += ret_val;
  }

  return SENT;
}


std::shared_ptr<tt::chat::comms::Command> 
tt::chat::comms::read_command(std::string& read_buf)
{
  std::shared_ptr<tt::chat::comms::Command> np(nullptr);
  if(read_buf.size()<4) return np;

  uint32_t msg_len;
  std::memcpy(&msg_len, read_buf.data(), sizeof(uint32_t));
  msg_len = ntohl(msg_len);
  if(read_buf.size()<msg_len + sizeof(uint32_t)) return np;

  std::shared_ptr<tt::chat::comms::Command> new_cmd = std::make_shared<tt::chat::comms::Command>();

  {
    std::istringstream payload(read_buf.substr(sizeof(msg_len), msg_len));
    cereal::PortableBinaryInputArchive archive(payload);
    new_cmd->serialize(archive);
    new_cmd->cmd_request = read_buf.substr(sizeof(msg_len), msg_len);
  }
  read_buf.erase(0, sizeof(msg_len) + msg_len);
  return new_cmd;
}
