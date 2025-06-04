#include "comms.h"
#include <cstdint>
#include <sstream>
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
  
}
