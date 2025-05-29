#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include "utils.h"
#include "classes/server.h"

int main() {
  const int kPort = 8080;
  Server server(kPort);
  server.start();
  return 0;
}