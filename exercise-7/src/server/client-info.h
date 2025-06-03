#ifndef CLIENT_INFO_H
#define CLIENT_INFO_H

#include <queue>
#include <string>
#include <memory>
#include "net/comms.h"

namespace tt::chat::server {

// Class to store metadata regarding client, including:
//  - client connection status
//  - client user name
//  - socket file descriptor
//  - queue of shared_ptr to pending server -> client commands
//  - whether current command has been interrupted due to blocking 
//  - also responsible for closing socket
//  - current channel
class ClientInfo {
  public:
    ClientInfo(std::string & user, int fd);
    ~ClientInfo();
    bool reset_queue();
    bool send_data();
    bool add_to_queue(std::shared_ptr<tt::chat::comms::Command> cmd_req);
    int get_channel();
    bool set_channel(int chan);

  private:
    std::string username;
    int sockfd;
    unsigned sent_size;
    int channel;
    std::queue<tt::chat::comms::Command> req_queue;
};

}

#endif