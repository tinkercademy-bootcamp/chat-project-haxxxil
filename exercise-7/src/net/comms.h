#ifndef COMMS_H
#define COMMS_H

#include <string>
#include <cereal/archives/portable_binary.hpp>

namespace tt::chat::comms {

std::string read_from_socket();
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

    bool serialize_req();
    bool deserialize_req();
    

private:
    template<class Archive>
    void serialize(Archive & archive)
    {
      archive(cmd, user, message);
    }
};

}

#endif