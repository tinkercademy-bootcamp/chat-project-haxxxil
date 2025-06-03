#ifndef COMMS_H
#define COMMS_H

#include <string>

namespace tt::chat::comms {
  std::string read_from_socket();
  int write_to_socket(char * message, int msg_size);
}

#endif