#ifndef COMMS_H
#define COMMS_H

#include <cstdint>
#include <memory>
#include <sstream>
#include <string>
#include <cstring>
#include <cereal/archives/portable_binary.hpp>
#include <cereal/types/string.hpp>
#include <arpa/inet.h>

namespace tt::chat::comms {

bool read_from_socket(int sockfd, std::string & readStr);
int write_to_socket(char * message, int msg_size);


class Command {
  public:
    enum CommandType {
      SEND_MSG,
      READ_MSG,
      CHANGE_CHAN,
      LIST_CHAN,
      CREATE_CHAN
    };

    CommandType cmd;
    std::string user;
    std::string cmd_request;
    std::string message;

    char * get_string_ptr();
    unsigned get_string_size();

    template<class Archive>
    void serialize(Archive & archive)
    {
      archive(cmd, user, message);
    }
};

class Message {
public:
  enum SEND_STATUS{
    SENT,
    BLOCKED,
    PARTIAL,
    ERROR
  };

  Message(std::shared_ptr<tt::chat::comms::Command> msg_cmd);
  SEND_STATUS send_message(int sockfd, int epollfd);

private:
  uint32_t sent_bytes;
  // final message is msg_len + cmd_ptr->cmd_request
  std::string msg_len;
  std::shared_ptr<tt::chat::comms::Command> cmd_ptr;
};

std::shared_ptr<tt::chat::comms::Command> read_command(std::string& read_buf);

}

#endif