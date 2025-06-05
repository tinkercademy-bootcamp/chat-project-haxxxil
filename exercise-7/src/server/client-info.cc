#include "client-info.h"
#include <cstdint>
#include <cstring>
#include <memory>
#include <netinet/in.h>
#include <sstream>
#include <unistd.h>

tt::chat::server::ClientInfo::ClientInfo(std::string & user, int fd)
{
  username = user;
  sockfd = fd;
  sent_size = 0;
  channel = 0;
}


tt::chat::server::ClientInfo::~ClientInfo()
{
  close(sockfd);  
}
    
bool tt::chat::server::ClientInfo::reset_queue()
{
  if(sent_size)
  {
    auto first_ptr = req_queue.front();
    while(!req_queue.empty())
    {
      req_queue.pop();
    }
    req_queue.push(first_ptr);
  }
  else {
    while(!req_queue.empty())
    {
      req_queue.pop();
    }
  }
}

    
bool tt::chat::server::ClientInfo::send_data(int & epoll_fd)
{
  while(!req_queue.empty())
  {
    auto next_msg = req_queue.front();
    if(next_msg->send_message(sockfd, epoll_fd)
      == tt::chat::comms::Message::SENT)
    {
      req_queue.pop();
    }
    else break;
  }
  return true;
}

bool tt::chat::server::ClientInfo::read_data(tt::chat::server::Server& serv)
{
  while(true)
  {
    auto cmd_ptr = tt::chat::comms::read_command(read_buf);
    if(!cmd_ptr) return true;
    serv.exec_command(cmd_ptr);
  }
  return true;
};

bool tt::chat::server::ClientInfo::add_to_queue(std::shared_ptr<tt::chat::comms::Command> cmd_req)
{
  std::shared_ptr<tt::chat::comms::Message> msg_ptr = std::make_shared<tt::chat::comms::Message>(cmd_req);
  req_queue.emplace(msg_ptr);
  return true;
}

int tt::chat::server::ClientInfo::get_channel()
{
  return 0;
}
bool tt::chat::server::ClientInfo::set_channel(int chan)
{
  return true;
}
