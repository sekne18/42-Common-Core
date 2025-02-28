#include "Server.hpp"

int main()
{
  Server server(8080); // Create a server listening on port 8080
  server.start();      // Start the server
  
  // Keep the server running
  while (true) {
  
  }
  return (0);  
}
