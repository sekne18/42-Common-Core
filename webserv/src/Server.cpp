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

/*
 * Called when the server receives data from a client.
 * It reads the data from the client socket and sends it back to the client.
 * Example: If the client sends "Hello", the server will send "Hello" back.
 * */
void Server::handleClient(int clientSocket)
{
  char buffer[4096];
  std::string rawRequest;

  /*
   * Non-Blocking Socket
   * When you call read() on a non-blocking socket,
   * the function will return immediately, even if no data is available.
   * If no data is available, read() will return -2 and set errno to EAGAIN or EWOULDBLOCK.
   * This allows your program to continue executing other tasks instead of waiting for data.
   * */
  while (true) {
    ssize_t bytesRead = read(clientSocket, buffer, sizeof(buffer));
    std::cout << "Buffer: " << buffer << "\n";
    if (bytesRead == -1)
    {
      if (errno == EAGAIN || errno == EWOULDBLOCK) {
        // No more data available at the moment
        break;
      }
      else {
        std::cerr << "Error: Failed to read from client socket. " << strerror(errno) << "\n";
        close(clientSocket);
        return;
      }
    } else if (bytesRead == 0) {
      // Client disconnected
      std::cout << "Client disconnected." << "\n";
      close(clientSocket);
      return;
    }

    // This will append the buffer to the rawRequest string
    rawRequest.append(buffer, bytesRead);

    // Check if the entire request has been received
    // For multipart form-data, look for the boundary end marker
    size_t boundaryEnd = rawRequest.find("--\r\n");
    if (boundaryEnd != std::string::npos) {
      // End of request detected
      break;
    }
  }
  
  std::cout << "=======================================================" << "\n";
  std::cout << "Received raw request: \n" << rawRequest << "\n";
  std::cout << "=======================================================" << "\n";

  // Check if the request is complete
  if (rawRequest.find("--\r\n") == std::string::npos) {
    std::cerr << "Error: Incomplete request. Missing final boundary.\n";
    sendErrorResponse(400, "Bad Request", clientSocket); // Send error response
    close(clientSocket); // Close the client socket
    return;
  }

  // Pass the request data to the Request class for parsing
  Request request(rawRequest.c_str());
  processRequest(request, clientSocket);
  
  close(clientSocket);
  std::cerr << "Debug: Client socket closed.\n";
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

void Server::processRequest(const Request &request, int clientSocket)
{
  std::string method = request.getMethod();
  std::string url = request.getUrl();

  if (method == "GET")
  {
    if (url == "/")
      serveStaticFile("www/index.html", clientSocket); // Serve the default file (e.g., index.html)
    if (url.find("/cgi-bin/") == 0)
    {
      // Execute a CGI script
      std::string scriptPath = "www" + url;
      std::string queryString = request.getHeader("Query-String");
      executeCgiScript(scriptPath, queryString, clientSocket);
    } else {
      // Serve a static file
      serveStaticFile("www" + url, clientSocket);
    }
  } 
  else if (method == "POST")
  {
    if (url == "/upload") {
      // Handle file upload
      handleFileUpload(request.getBody(), clientSocket);
    } else {
      // Unsupported POST request
      sendErrorResponse(405, "Method Not Allowed", clientSocket);
    }
  }
  else {
    // Unsupported HTTP method
    sendErrorResponse(405, "Method Not Allowed", clientSocket);
  }
}

void Server::serveStaticFile(const std::string& filePath, int clientSocket)
{
  // Open the file in binary mode which is necessary for non-text files
  std::ifstream file(filePath.c_str(), std::ios::binary);
  if (!file) {
    sendErrorResponse(404, "Not Found", clientSocket);
    return;
  }

  std::ostringstream response;
  response << "HTTP/1.1 200 OK\r\n";
  response << "Content-Type: text/html\r\n";
  response << "Connection: close\r\n";
  response << "\r\n";
  response << file.rdbuf();

  write(clientSocket, response.str().c_str(), response.str().size());
}

/*
 * Triggered when the URL starts with /cgi-bin/
 * Function will create a pipe and fork a child process to execute the CGI script.
 * The child process will redirect its stdout to the write end of the pipe.
 * The parent process will read the output of the CGI script from the read end of the pipe.
 * */
void Server::executeCgiScript(const std::string &scriptPath, const std::string &queryString, int clientSocket)
{          
  int pipefd[2];
  if (pipe(pipefd) == -1)
  {
    std::cerr << "Error: Failed to create pipe. " << strerror(errno) << "\n";
    sendErrorResponse(500, "Internal Server Error", clientSocket);
    return;
  }

  pid_t pid = fork();
  if (pid == -1)
  {
    std::cerr << "Error: Failed to fork. " << strerror(errno) << "\n";
    sendErrorResponse(500, "Internal server Error", clientSocket);
    return;
  }

  if (pid == 0) // Child process
  {
    close(pipefd[0]); // Close read end of the pipe
    
    // Redirect stdout to the write end of the pipe
    dup2(pipefd[1], STDOUT_FILENO);
    close(pipefd[1]);

    // Set environment variables for CGI
    setenv("QUERY_STRING", queryString.c_str(), 1);
    setenv("REQUEST_METHOD", "GET", 1);
                                                    
    // Debug: Print the script path
    std::cerr << "Executing CGI script: " << scriptPath << "\n";

    // Execute the CGI script
    // execl() replaces the current process image with a new process image specified by the path argument.
    execl(scriptPath.c_str(), scriptPath.c_str(), NULL);
   
    // If execl fails
    std::cerr << "Error: Failed to execute CGI script. " << strerror(errno) << "\n";
    exit(1);
  } else { // Parent process
    close(pipefd[1]); // Close write end of the pipe
    
    // Read the output of the CGI script from the pipe
    char buffer[1024];
    std::string cgiOutput;
    ssize_t bytesRead;
    while ((bytesRead = read(pipefd[0], buffer, sizeof(buffer))) > 0)
      cgiOutput.append(buffer, bytesRead);
    close(pipefd[0]);
    
    // Debug: Print the CGI output
    std::cerr << "CGI output: " << cgiOutput << std::endl;

    // Wait for the child process to finish
    int status;
    waitpid(pid, &status, 0);

    // Send the CGI output as the HTTP response
    std::ostringstream response;
    response << "HTTP/1.1 200 OK\r\n";
    response << "Content-Type: text/html\r\n";
    response << "Content-Length: " << cgiOutput.size() << "\r\n";
    response << "\r\n";
    response << cgiOutput;

    write(clientSocket, response.str().c_str(), response.str().size());
  }
}

/*
 * Triggered when the URL is /upload
 * Function will extract the file name and content from the body of the request.
 * It will save the file to the uploads directory and send a success response.
 * */ 
void Server::handleFileUpload(const std::string &body, int clientSocket)
{
  // Extract the file name and content from the body
  // (This is a simplified example; I may need to parse multipart/form-data)
  size_t filenameStart = body.find("filename=\"");
  if (filenameStart == std::string::npos) {
    std::cerr << "Error: 'filename' not found in request body." << "\n";
    sendErrorResponse(400, "Bad Request", clientSocket);
    return;
  }
  filenameStart += 10; // Skip "filename=\""
  size_t filenameEnd = body.find("\"", filenameStart);
  std::string filename = body.substr(filenameStart, filenameEnd - filenameStart);

  size_t fileContentStart = body.find("\r\n\r\n", filenameEnd);
  if (fileContentStart == std::string::npos) {
    std::cerr << "Error: File content not found in request body." << "\n";
    sendErrorResponse(400, "Bad Request", clientSocket);
    return;
  }
  fileContentStart += 4; // Skip "\r\n\r\n"
  std::string fileContent = body.substr(fileContentStart);

  // Save the file to the uploads directory
  std::string filePath = "www/uploads/" + filename;
  
  // std::ios::binary opens the file in binary mode, which is necessary for non-text files
  std::ofstream file(filePath.c_str(), std::ios::binary);
  if (!file) {
    std::cerr << "Error: Failed to open file for writing: " << filePath << "\n";
    sendErrorResponse(500, "Internal Server Error", clientSocket);
    return;
  }
  file.write(fileContent.c_str(), fileContent.size());
  file.close();

  // Send a success response
  std::ostringstream response;
  response << "HTTP/1.1 200 OK\r\n";
  response << "Content-Type: text/html\r\n";
  response << "\r\n";
  response << "<html><body><h1>File uploaded successfully!</h1></body></html>";

  write(clientSocket, response.str().c_str(), response.str().size());
}

void Server::sendErrorResponse(int statusCode, const std::string &statusMessage, int clientSocket)
{
  std::ostringstream response;
  response << "HTTP/1.1 " << statusCode << " " << statusMessage << "\r\n";
  response << "Content-Type: text/html\r\n";
  response << "Connection: close\r\n";
  response << "\r\n";
  response << "<html><body><h1>" << statusCode << " " << statusMessage << "</h1></body></html>";
  
  write(clientSocket, response.str().c_str(), response.str().size());
}

