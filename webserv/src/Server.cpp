#include "Server.hpp"
#include "Client.hpp"
#include "NetworkManager.hpp"
#include "Response.hpp"
#include "Config.hpp"

/*
* Server manages high-level server operations, such as starting and stopping the server,
* accepting new client connections, and processing client events.
* It uses a NetworkManager object to handle low-level network operations.
 * */
Server::Server(const Config& config) 
  : _port(config.getPort()), 
    _serverSocket(-1), 
    _epollFd(-1), 
    _isRunning(false),
    _config(config),
    _networkManager(NetworkManager(_port))
{
  std::cout << "Server initiated on port: " << _port << "\n";
}

Server::~Server()
{
  stop();
}

void Server::stop()
{
  _networkManager.closeSocket(_serverSocket);
  _networkManager.closeEpoll(_epollFd);
  _isRunning = false;
}

void Server::start()
{
  try {
    _serverSocket = _networkManager.createSocket();
    _networkManager.bindSocket(_serverSocket, _serverAddress);
    _networkManager.listenForConnections(_serverSocket);
    _epollFd = _networkManager.setupEpoll(_serverSocket);
    _isRunning = true;
    
    // Resize the events vector to hold up to 64 events
    _events.resize(64);

    // Handle events (this will block)
    handleEvents();
  }
  catch (const std::exception& e) {
    std::cerr << e.what() << "\n";
    stop();
  }
}

void Server::handleEvents()
{
  while (_isRunning)
  {
    // epoll_wait() waits for events on the file descriptor in the epoll set
    int numEvents = epoll_wait(_epollFd, _events.data(), _events.size(), -1);
    if (numEvents == -1)
    {
      std::cerr << "Error: epoll_wait failed. " << strerror(errno) << "\n";
      continue;
    }

    for (int i = 0; i < numEvents; ++i)
    {
      if (_events[i].data.fd == _serverSocket)
        acceptClient(); // New client connection
      else
        processClientEvent(_events[i].data.fd); // Handle client data
    }
  }
}

void Server::acceptClient()
{
  Client client = _networkManager.acceptConnection(_serverSocket, _epollFd);
  _clients[client.getSocket()] = client;
}

void Server::processClientEvent(int clientSocket)
{
  if (_clients.find(clientSocket) == _clients.end()) {
    std::cerr << "Error: Client socket not found in client map.\n";
    return;
  }

  Client& client = _clients[clientSocket];
  if (!client.readRequest()) {
    _clients.erase(clientSocket);
    return;
  }

  if (client.hasCompleteRequest()) {
    Request request = client.getRequest();
    Response response(_config);
    response.processRequest(request, clientSocket);
    _clients.erase(clientSocket);
  }
}
