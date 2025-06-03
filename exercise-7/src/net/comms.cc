#include "comms.h"
#include <unistd.h>

// Returns false if connection has closed.
bool tt::chat::comms::read_from_socket(int sockfd, std::string & readStr)
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

int tt::chat::comms::write_to_socket(char *message, int msg_size) {
  return 0;
}
