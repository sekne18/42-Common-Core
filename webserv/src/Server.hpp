#ifndef SERVER_HPP
#define SERVER_HPP

#include "Request.hpp"
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <iostream>
#include <cerrno>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>
#include <vector>
#include <fcntl.h>
#include <cstdlib>

class Server
{
public:
  Server(int port);
  ~Server();
  void start(); // Start the server
  void stop(); // Stop the server

private:
  void createSocket(); // Create the server socket
  void bindSocket(); // Bind listening for connection
  void listenForConnections(); // Start listening for connections
  void setupEpoll(); // Setup epoll for event handling
  void handleEvents(); // Handle epoll events
  void acceptClient(); // Accept incoming client connection
  void handleClient(int clientSocket); // Handle client connection
  void serveStaticFile(const std::string &filePath, int clientSocket);
  void processRequest(const Request &request, int clientSocket);
  void executeCgiScript(const std::string &scriptPath, const std::string &queryString, int clientSocket);
  void handleFileUpload(const std::string &body, int clientSocket);
  void sendErrorResponse(int statusCode, const std::string &statusMessage, int clientSocket);

  int _port; // Port to listen to
  int _serverSocket; // Server socket file descriptor
  int _epollFd; // Epoll file descriptor
  struct sockaddr_in _serverAddress; // Server address structure
  bool _isRunning; // Server running state
  std::vector<struct epoll_event> _events; // Store epoll events
};

#endif // SERVER_HPP
