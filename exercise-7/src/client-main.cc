#include <arpa/inet.h>
#include <cstdlib>
#include <iostream>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <thread>

#include "client/chat-client.h"
#include "net/misc.h"

const std::string main_kServerAddress = "127.0.0.1";
tt::chat::client::Client main_client{kPort, main_kServerAddress};


namespace {
std::string read_args(int argc, char *argv[]) {
  using namespace tt::chat;
  std::string message = "Hello from client";
  if (argc == 1) {
    std::cout << "Usage: " << argv[0] << " <message>\n";
    exit(EXIT_FAILURE);
  }
  if (argc > 1) {
    message = argv[1];
  }
  return message;
}
} // namespace

void worker1()
{
  main_client.send_and_receive_message();
}


void worker2()
{
  main_client.input_handler();
}
int main() {

  std::thread t1(worker1);
  std::thread t2(worker2);

  t1.join();
  t2.join();

  return 0;
}
