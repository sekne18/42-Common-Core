#include "CGI.hpp"
#include <errno.h>
#include <stdlib.h>

/*
 * Handles CGI script execution.
 * */
CGI::CGI(const Config& config) : _config(config)
{
}

void CGI::executeScript(const std::string& scriptPath, const std::string& queryString, int clientSocket)
{          
  int pipefd[2];
  if (pipe(pipefd) == -1)
  {
    std::cerr << "Error: Failed to create pipe. " << strerror(errno) << "\n";
    throw std::runtime_error("Failed to create pipe for CGI execution");
  }

  pid_t pid = fork();
  if (pid == -1)
  {
    std::cerr << "Error: Failed to fork. " << strerror(errno) << "\n";
    close(pipefd[0]);
    close(pipefd[1]);
    throw std::runtime_error("Failed to fork for CGI execution");
  }

  if (pid == 0) // Child process
  {
    try {
      setupChildProcess(pipefd, scriptPath, queryString);
    } catch (const std::exception& e) {
      std::cerr << "Error in child process: " << e.what() << "\n";
      exit(1);
    }
  } else { // Parent process
    handleParentProcess(pipefd, pid, clientSocket);
  }
}

void CGI::setupChildProcess(int pipefd[2], const std::string& scriptPath, const std::string& queryString)
{
  close(pipefd[0]); // Close read end of the pipe
    
  // Redirect stdout to the write end of the pipe
  if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
    std::cerr << "Error: Failed to redirect stdout. " << strerror(errno) << "\n";
    close(pipefd[1]);
    exit(1);
  }
  close(pipefd[1]);

  // TODO: Not allowed to use setenv()
  // Set environment variables for CGI
  setenv("QUERY_STRING", queryString.c_str(), 1);
  setenv("REQUEST_METHOD", "GET", 1);
  setenv("SERVER_SOFTWARE", "WebServ/1.0", 1);
  setenv("SERVER_NAME", _config.getServerName().c_str(), 1);
  setenv("SERVER_PORT", std::to_string(_config.getPort()).c_str(), 1);
  setenv("DOCUMENT_ROOT", _config.getDocumentRoot().c_str(), 1);

  // Debug: Print the script path
  std::cerr << "Executing CGI script: " << scriptPath << "\n";

  // Execute the CGI script
  // execl() replaces the current process image with a new process image specified by the path argument.
  execl(scriptPath.c_str(), scriptPath.c_str(), NULL);
 
  // If execl fails
  std::cerr << "Error: Failed to execute CGI script. " << strerror(errno) << "\n";
  exit(1);
}

void CGI::handleParentProcess(int pipefd[2], pid_t pid, int clientSocket)
{
  close(pipefd[1]); // Close write end of the pipe
  
  // Read the output of the CGI script from the pipe
  std::string cgiOutput = readFromPipe(pipefd[0]);
  close(pipefd[0]);
  
  // Debug: Print the CGI output
  std::cerr << "CGI output: " << cgiOutput << std::endl;

  // Wait for the child process to finish
  int status;
  waitpid(pid, &status, 0);

  if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
    // Child process exited with an error
    std::cerr << "CGI script exited with status: " << WEXITSTATUS(status) << "\n";
    sendErrorResponse(500, "Internal Server Error", clientSocket);
    return;
  }

  // Send the CGI output as the HTTP response
  sendCgiResponse(cgiOutput, clientSocket);
}

std::string CGI::readFromPipe(int pipefd)
{
  char buffer[1024];
  std::string cgiOutput;
  ssize_t bytesRead;
  
  while ((bytesRead = read(pipefd, buffer, sizeof(buffer))) > 0) {
    cgiOutput.append(buffer, bytesRead);
  }
  
  if (bytesRead == -1) {
    std::cerr << "Error reading from pipe: " << strerror(errno) << "\n";
  }
  
  return cgiOutput;
}

void CGI::sendCgiResponse(const std::string& cgiOutput, int clientSocket)
{
  // Check if the CGI script included HTTP headers
  size_t headerEnd = cgiOutput.find("\r\n\r\n");
  bool hasHeaders = headerEnd != std::string::npos && 
                   cgiOutput.find("Content-Type:") != std::string::npos;
  
  std::ostringstream response;
  
  if (!hasHeaders) {
    // No headers found, add our own
    response << "HTTP/1.1 200 OK\r\n";
    response << "Content-Type: text/html\r\n";
    response << "Content-Length: " << cgiOutput.size() << "\r\n";
    response << "\r\n";
  }
  
  response << cgiOutput;

  write(clientSocket, response.str().c_str(), response.str().size());
}

void CGI::sendErrorResponse(int statusCode, const std::string& statusMessage, int clientSocket)
{
  std::ostringstream response;
  response << "HTTP/1.1 " << statusCode << " " << statusMessage << "\r\n";
  response << "Content-Type: text/html\r\n";
  response << "Connection: close\r\n";
  response << "\r\n";
  response << "<html><body><h1>" << statusCode << " " << statusMessage << "</h1>";
  response << "<p>CGI Script Execution Failed</p></body></html>";
  
  write(clientSocket, response.str().c_str(), response.str().size());
}
