#include "Server.hpp"

Server::Server(int port) : _port(port), _serverSocket(-1), _epollFd(-1), _isRunning(false)
{
  std::cout << "Server initiated on port: " << _port << "\n";
}

Server::~Server()
{
  stop();
}

void Server::stop()
{
  if (_serverSocket != -1)
  {
    close(_serverSocket);
    std::cout << "Server socket closed." << "\n";
  }
  if (_epollFd != -1)
  {
    close(_epollFd);
    std::cout << "Epoll instance closed." << "\n";
  }
  _isRunning = false;
}

void Server::start()
{
  try {
    createSocket();
    bindSocket();
    listenForConnections();
    setupEpoll();
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

void Server::handleClient(int clientSocket)
{
  char buffer[1024];
  ssize_t bytesRead = read(clientSocket, buffer, sizeof(buffer));
  if (bytesRead == -1)
  {
    std::cerr << "Error: Failed to read from client socket, " << strerror(errno) << "\n";
    close(clientSocket);
    return ;
  } else if (bytesRead == 0) {
   
    // Client disconnected
    std::cout << "Client disconnected." << "\n";
    close(clientSocket);
    return;
  }

  // Echo the data back to the client
  write(clientSocket, buffer, bytesRead);
}

void Server::acceptClient()
{
  struct sockaddr_in clientAddress;
  socklen_t clientAddressLength = sizeof(clientAddress);

  /*
   * Accepts an incoming client connection.
   * It returns a new socket file descriptor for the client, which you can use to communicate with that client.
   * Accept params: server socket, client address, client address length
   *    sockfd: The file descriptor of the server's listening socket (created with socket() and bound with bind())
   *    addr: A pointer to a sockaddr_in structure that will be filled with the client's address information.
   *    addrln: A pointer to a socklen_t variable that specifies the size of the addr structure. It is updated to the actual 
   *            size of the client's address.
   */
  int clientSocket = accept(_serverSocket, (struct sockaddr*)&clientAddress, &clientAddressLength);
  if (clientSocket == -1)
  {
    std::cerr << "Error: Failed to accept client connection. " << strerror(errno) << "\n";
    return ;
  }

  // Set the client socket to non-blocking mode
  int flags = fcntl(clientSocket, F_GETFL, 0);

  //Sets the client socket to non-blocking mode. This ensures that read() and write() operations don't block the server.
  fcntl(clientSocket, F_SETFL, flags | O_NONBLOCK);
  
  // Add the client socket to the epoll set
  struct epoll_event event;

  /*
   * EPOLLET - Enables edge-triggered mode for the client socket.
   * This means epoll_wait() will only notify you when new data arrives, not when there is still data in the buffer.
   */
  event.events = EPOLLIN | EPOLLET; // Monitor for incoming data (edge-triggered)
  event.data.fd = clientSocket;
  if (epoll_ctl(_epollFd, EPOLL_CTL_ADD, clientSocket, &event) == -1)
  {
    std::cout << "Error: Failed to add client socket to epoll. " << strerror(errno) << "\n";
    close(clientSocket);
    return;
  }
  std::cout << "Client connected from " << inet_ntoa(clientAddress.sin_addr) << ":" << ntohs(clientAddress.sin_port) << "\n";
}

void Server::setupEpoll()
{
  // Creates an epoll instance
  _epollFd = epoll_create1(0);
  if (_epollFd == -1)
    throw std::runtime_error("Error: Failed to create epoll instance. " + std::string(strerror(errno)));
  
  // Add the server socket to the epoll set
  struct epoll_event event;
  event.events = EPOLLIN; // Monitor for incoming data
  event.data.fd = _serverSocket;

  // epoll_ctl() Add the server socket to the epoll set of monitor for incoming connections (EPOLLIN)
  if (epoll_ctl(_epollFd, EPOLL_CTL_ADD, _serverSocket, &event) == -1)
  {
    close(_epollFd);
    throw std::runtime_error("Error: Failed to add server socket to epoll. " + std::string(strerror(errno)));
  }
  std::cout << "Epoll set up successfully." << "\n"; 
}

// Handle epoll events
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

    /*
     * If the server socket triggers an event, a new client connection is accepted using accept().
     * If a client socket triggers and event, the server reads data from the client and echoes it back.
     * */
    for (int i = 0; i < numEvents; ++i)
    {
      if (_events[i].data.fd == _serverSocket)
        acceptClient(); // New client connection
      else
        handleClient(_events[i].data.fd); // Handle client data
    }
  }
}

// Starts listening for incoming connections
void Server::listenForConnections()
{
  if (listen(_serverSocket, 10) == -1)
  {
    close(_serverSocket);
    throw std::runtime_error("Error: Failed to listen to socket. " + std::string(strerror(errno)));
  }
  std::cout << "Server is listening on port " << _port << "..." << "\n";
}

// Bindsocket to port
void Server::bindSocket()
{
  memset(&_serverAddress, 0, sizeof(_serverAddress));
  _serverAddress.sin_family = AF_INET;
  _serverAddress.sin_addr.s_addr = INADDR_ANY;

  // htons() converts the port number to network byte order
  _serverAddress.sin_port = htons(_port);
  
  if (bind(_serverSocket, (struct sockaddr*)&_serverAddress, sizeof(_serverAddress)) == -1)
  {
    close(_serverSocket);
    throw std::runtime_error("Error: Failed to bind socket. " + std::string(strerror(errno)));
  }
  std::cout << "Socket bound to port " << _port << "\n";
}

void Server::createSocket()
{
  // Socket is used to listen for incoming connections.
  // AF_INET - IPv4, SOCK_STREAM - TCP
  _serverSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (_serverSocket == -1)
    throw std::runtime_error("Error: Failed to create socket. " + std::string(strerror(errno)));
  std::cout << "Socket created successfully." << "\n";
}
