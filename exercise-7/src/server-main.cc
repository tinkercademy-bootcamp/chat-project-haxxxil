#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "server/chat-server.h"
#include "net/misc.h"

int main() {

  tt::chat::server::Server server(kPort);
  server.handle_connections();

  return 0;
}
