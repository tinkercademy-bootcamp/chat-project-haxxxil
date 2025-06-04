#include "client-info.h"
#include <cstdint>
#include <cstring>
#include <memory>
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

    
bool tt::chat::server::ClientInfo::send_data()
{
  return true;
}

bool tt::chat::server::ClientInfo::read_data(tt::chat::server::Server& serv)
{
  while(true)
  {
    if(read_buf.size()<4) break;

    uint32_t msg_len;
    std::memcpy(&msg_len, read_buf.data(), sizeof(uint32_t));
    if(read_buf.size()<msg_len + sizeof(uint32_t)) break;

    std::shared_ptr<tt::chat::comms::Command> new_cmd = std::make_shared<tt::chat::comms::Command>();

    {
      std::istringstream payload(read_buf.substr(sizeof(msg_len), msg_len));
      cereal::PortableBinaryInputArchive archive(payload);
      new_cmd->serialize(archive);
    }
    read_buf.erase(0, sizeof(msg_len) + msg_len);
    serv.exec_command(new_cmd);
  }
};

bool tt::chat::server::ClientInfo::add_to_queue(std::shared_ptr<tt::chat::comms::Command> cmd_req)
{
  req_queue.emplace(cmd_req);
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
