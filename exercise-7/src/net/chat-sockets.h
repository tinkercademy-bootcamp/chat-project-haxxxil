#ifndef CHAT_SOCKETS_H
#define CHAT_SOCKETS_H

#include <arpa/inet.h>
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "../utils.h"

namespace tt::chat::net {

int create_socket();
void set_nonblocking_socket(int sockfd);

sockaddr_in create_address(int port);

} // namespace tt::chat::net

#endif // CHAT_SOCKETS_H
