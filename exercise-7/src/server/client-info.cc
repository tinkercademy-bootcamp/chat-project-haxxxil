#include "client-info.h"
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

bool tt::chat::server::ClientInfo::read_data()
{

};

bool tt::chat::server::ClientInfo::add_to_queue(std::shared_ptr<tt::chat::comms::Command> cmd_req)
{
  // req_queue.push(cmd_req);
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
