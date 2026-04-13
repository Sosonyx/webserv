# WebServ Project

  <p align="center">
    For further information about 42cursus and its projects, see <a href="https://42.fr/le-campus-de-paris/diplome-informatique/"><b>42school</b></a>.
  </p>
  
  <p>
    <img src="https://img.shields.io/badge/language-C%2B%2B-blue?style=for-the-badge" />
    <img src="https://img.shields.io/github/repo-size/Sosonyx/webserv?style=for-the-badge&logo=github">
    <img src="https://img.shields.io/github/languages/count/Sosonyx/webserv?style=for-the-badge" />
    <img src="https://img.shields.io/github/languages/top/Sosonyx/webserv?style=for-the-badge" />
    <img src="https://img.shields.io/github/last-commit/Sosonyx/webserv?style=for-the-badge" />
  </p>

 <div align="center" style="font-size:1.3em; line-height:2;">
  <span><a href="#about-project" style="text-decoration:none; color:inherit;">📜 About Project</a></span>
  &nbsp;•&nbsp;
  <span><a href="#mandatory-part" style="text-decoration:none; color:inherit;">🔷 Mandatory Part</a></span>
  &nbsp;•&nbsp;
  <span><a href="#bonus-part" style="text-decoration:none; color:inherit;">🌟 Bonus Part</a></span>
  &nbsp;•&nbsp;
  <span><a href="#usage" style="text-decoration:none; color:inherit;">👨‍💻 Usage</a></span>
</div>

---

## <a name="about-project"></a>📜 About Project

> 42 School WebServ project: Create a minimal HTTP/1.1 web server inspired by **NGINX**.  
> Learn **socket programming**, **HTTP protocol**, **I/O multiplexing**, and **connection management**.

```
TL;DR: Build a web server from scratch.  
- Parse HTTP requests and generate responses.  
- Handle multiple client connections concurrently.  
- Serve static files and execute CGI scripts.  
- Support virtual hosts and custom configurations.
```

> [!NOTE]    
> - Norminette compliant C++98 code.  
> - Classes and OOP principles required.  
> - Only allowed functions.

**Contributors** : Sosonyx

---

## <a name="mandatory-part"></a>🔷 Mandatory Part

A **fully functional HTTP/1.1 web server** supporting:

### Core Features

- **HTTP Protocol**: Parse HTTP/1.1 requests (GET, POST, DELETE)
- **Socket Programming**: Create TCP/IP sockets and listen for connections
- **Connection Handling**: 
  - Accept and manage multiple client connections
  - Handle concurrent requests without threads
  - Properly close connections and manage file descriptors
- **Response Generation**: Build valid HTTP responses with headers and body
- **Static File Serving**:
  - Serve HTML, CSS, JavaScript, images, and other static assets
  - Directory listing capabilities
  - File type detection (MIME types)
- **Request Methods**:
  - `GET` - retrieve files and resources
  - `POST` - submit data and forms
  - `DELETE` - remove files from server
- **Redirections**: HTTP 301/302/307/308 redirects
- **Configuration File**:
  - Define multiple servers (virtual hosts)
  - Set root directory, ports, and server names
  - Configure upload directories
  - Define allowed HTTP methods per location
- **CGI Execution**:
  - Execute CGI scripts (PHP, Python, Bash, etc.)
  - Pass environment variables to scripts
  - Capture and return script output
- **Error Handling**:
  - HTTP error pages (400, 403, 404, 405, 413, 500, 501, etc.)
  - Custom error pages support
- **Chunked Transfer Encoding**: Handle client uploads properly

### Program Behavior

```
The server starts and reads configuration file.
Server binds to specified ports and listens for connections.
Accepts incoming client requests.
Parses HTTP headers and request body.
Processes request and generates appropriate response.
Sends response back to client.
Manages connection (keep-alive or close).
Process repeats until server shutdown.
```

### Example Usage

```bash
$ ./webserv
# Listening on port 8080...

# In another terminal:
$ curl http://localhost:8080/
$ curl -X POST -d "name=value" http://localhost:8080/cgi-bin/script.php
$ curl -X DELETE http://localhost:8080/uploads/file.txt
```

### Configuration File Example

```nginx
server {
    listen       8080;
    server_name  localhost;
    
    root         /var/www/html;
    index        index.html index.htm;
    
    client_max_body_size 1m;
    
    location / {
        allow_methods GET;
    }
    
    location /upload {
        allow_methods POST;
        client_max_body_size 10m;
    }
    
    location /cgi-bin {
        allow_methods GET POST;
        cgi_pass     /usr/bin/php-cgi;
    }
    
    error_page 404 /404.html;
}
```

---

## <a name="bonus-part"></a>🌟 Bonus Part

Advanced web server features:

### Bonus Features

- **Keep-Alive Connections**: 
  - Reuse TCP connections for multiple requests
  - Configurable timeout values
  - Automatic connection closure
  
- **Multiple Servers**:
  - Listen on multiple ports simultaneously
  - Support for different hostnames
  - Port-based and name-based virtual hosting
  
- **Advanced Configuration**:
  - Location-based routing and settings
  - Alias and rewrite rules
  - Custom directory index pages
  - Autoindex (directory listing) on/off
  
- **Full CGI Support**:
  - Execute any CGI script
  - Proper environment variable setup
  - Request/response piping
  - Timeout handling for long-running scripts
  
- **Security Features**:
  - Custom error pages for better UX
  - Request timeout handling
  - Large file upload protection
  - Access control per location
  
- **HTTP/1.1 Compliance**:
  - Persistent connections
  - Chunked transfer encoding
  - Proper status codes
  - Standard HTTP headers
  
- **Advanced I/O**:
  - Non-blocking socket operations
  - select/poll/epoll multiplexing
  - Efficient request parsing
  - Streaming file serving

### Example Bonus Usage

```bash
# Keep-alive connections
$ curl -v http://localhost:8080/file1.html http://localhost:8080/file2.html

# Virtual hosts
$ curl -H "Host: api.example.com" http://localhost:8080/endpoint
$ curl -H "Host: www.example.com" http://localhost:8080/

# CGI script execution
$ curl http://localhost:8080/cgi-bin/time.sh

# File upload with progress
$ curl -X POST -F "file=@large.zip" http://localhost:8080/upload

# Directory listing
$ curl http://localhost:8080/files/
```

---

## <a name="usage"></a>👨‍💻 Usage

### Requirements

- C++ language (C++98)
- GCC/Clang compiler with C++98 support
- Linux/Unix system with POSIX compliance
- Standard C++ library

### Compiling the Program

**Mandatory Part:**

```shell
$ cd path/to/webserv && make
```

**Bonus Part:**
```shell
$ cd path/to/webserv && make bonus
```

### Running the Program

**Default configuration:**
```shell
$ ./webserv
# or with custom config file
$ ./webserv config/webserv.conf
```

**With custom port:**
```shell
$ ./webserv config/webserv.conf
```

### Example Session

```shell
$ ./webserv config/webserv.conf
WebServ listening on ports: 8080, 8081
Press Ctrl+C to shutdown...

# In another terminal:
$ curl http://localhost:8080/
<!DOCTYPE html>
<html>
<head><title>Welcome</title></head>
<body><h1>Welcome to WebServ</h1></body>
</html>

$ curl -X POST -d "name=John" http://localhost:8080/submit
Success: Data received

$ curl -X DELETE http://localhost:8080/uploads/temp.txt
File deleted successfully

$ curl http://localhost:8080/nonexistent
<html><body><h1>404 Not Found</h1></body></html>
```

---

## <a name="project-structure"></a>📁 Project Structure

```
webserv/
├── Makefile                     # Build configuration
├── README.md                    # This file
├── webserv.conf                 # Default configuration
├── includes/                    # Header files
│   ├── WebServ.hpp
│   ├── Server.hpp
│   ├── Client.hpp
│   ├── Request.hpp
│   ├── Response.hpp
│   ├── ConfigParser.hpp
│   └── ...
├── srcs/                        # Source files
│   ├── main.cpp
│   ├── WebServ.cpp             # Main server class
│   ├── Server.cpp              # Individual server instances
│   ├── Client.cpp              # Client connection handling
│   ├── Request.cpp             # HTTP request parsing
│   ├── Response.cpp            # HTTP response generation
│   ├── ConfigParser.cpp        # Configuration file parser
│   ├── CGI.cpp                 # CGI script execution
│   └── utils/                  # Utility functions
├── www/                         # Static website files
│   ├── index.html
│   ├── 404.html
│   ├── 50x.html
│   ├── css/
│   ├── js/
│   └── uploads/
└── cgi-bin/                     # CGI scripts
    ├── script.php
    ├── time.sh
    └── ...
```

---

## 🌊 Non-Blocking I/O and Socket Management

A key concept in WebServ is managing **multiple concurrent connections** without threads using **non-blocking sockets** and **I/O multiplexing**.

### What is Non-Blocking I/O?

Non-blocking sockets allow your program to **check if data is available** without waiting indefinitely. Combined with **multiplexing** (`select`, `poll`, `epoll`), you can handle thousands of concurrent connections.

### Event Loop Architecture

```
┌─────────────────────────────────────┐
│   Initialize Server & Listen        │
└────────────┬────────────────────────┘
             │
             ▼
┌─────────────────────────────────────┐
│   Set up Select/Poll/Epoll          │
│   (Monitor all file descriptors)    │
└────────────┬────────────────────────┘
             │
             ▼
┌─────────────────────────────────────┐
│   Wait for Events (timeout)         │
│   (Connection request, data ready)  │
└────────────┬────────────────────────┘
             │
        ┌────┴────┐
        ▼         ▼
    ┌────────┐ ┌────────────┐
    │ Accept │ │ Read/Write │
    │ new    │ │ existing   │
    │client  │ │connections│
    └────────┘ └────────────┘
        │         │
        └────┬────┘
             │
             ▼
    ┌──────────────────────┐
    │ Process HTTP Request │
    │ Generate Response    │
    │ Handle CGI if needed │
    └──────────────────────┘
             │
             ▼
    ┌──────────────────────┐
    │ Send Response Data   │
    │ Manage Connections   │
    └──────────────────────┘
             │
             └──────────────┐
                            ▼
                      (Loop back to select)
```

### Select-Based Implementation

```cpp
while (server_running)
{
    FD_ZERO(&read_set);
    FD_ZERO(&write_set);
    
    // Add server socket to listen for new connections
    FD_SET(server_socket, &read_set);
    int max_fd = server_socket;
    
    // Add all client sockets
    for (auto &client : clients)
    {
        FD_SET(client.socket, &read_set);
        if (client.has_data_to_send())
            FD_SET(client.socket, &write_set);
        max_fd = std::max(max_fd, client.socket);
    }
    
    // Wait for activity (non-blocking if timeout = 0)
    int activity = select(max_fd + 1, &read_set, &write_set, NULL, &timeout);
    
    if (activity > 0)
    {
        // New connection incoming
        if (FD_ISSET(server_socket, &read_set))
            accept_new_client();
        
        // Existing clients have data ready
        for (auto &client : clients)
        {
            if (FD_ISSET(client.socket, &read_set))
                read_request(client);
            if (FD_ISSET(client.socket, &write_set))
                send_response(client);
        }
    }
}
```

### Request Parsing State Machine

```cpp
enum RequestState {
    PARSING_REQUEST_LINE,
    PARSING_HEADERS,
    PARSING_BODY,
    COMPLETE,
    ERROR
};

class Client {
    RequestState state;
    std::string buffer;
    Request request;
    
    bool read_data(int socket)
    {
        char chunk[1024];
        int n = recv(socket, chunk, sizeof(chunk), 0);
        if (n <= 0) return false;
        
        buffer.append(chunk, n);
        
        while (!buffer.empty())
        {
            switch (state)
            {
                case PARSING_REQUEST_LINE:
                    if (has_complete_line(buffer))
                        parse_request_line(buffer);
                    break;
                    
                case PARSING_HEADERS:
                    if (has_complete_headers(buffer))
                        parse_headers(buffer);
                    break;
                    
                case PARSING_BODY:
                    if (has_complete_body(buffer, request.content_length))
                        parse_body(buffer);
                    state = COMPLETE;
                    break;
            }
            if (state == ERROR || state == COMPLETE)
                break;
        }
        return true;
    }
};
```

### Benefits of This Architecture

| Feature | Benefit |
|---------|---------|
| **Non-Blocking Sockets** | Single thread handles thousands of connections |
| **Select/Poll/Epoll** | Efficiently wait for I/O without busy-waiting |
| **State Machines** | Parse requests incrementally as data arrives |
| **Memory Efficient** | No thread overhead, minimal per-connection state |
| **Scalability** | Handles high concurrent load on single core |
| **Fair Scheduling** | All connections get CPU time |

---

## Key Learning Outcomes

✅ Understanding **TCP/IP sockets** and network programming  
✅ **HTTP/1.1 protocol** implementation and semantics  
✅ **Non-blocking I/O** and asynchronous programming  
✅ **I/O multiplexing** (`select`, `poll`, `epoll`)  
✅ **State machines** for protocol parsing  
✅ **CGI (Common Gateway Interface)** execution  
✅ **Process management** (`fork`, `pipe`, `execve`)  
✅ **Configuration parsing** and server setup  
✅ **Memory management** and resource cleanup  
✅ **OOP design** with C++98 classes  
✅ **Performance optimization** for concurrent connections  
✅ **HTTP error handling** and edge cases  

---

## Testing the Server

```bash
# Start the server
$ ./webserv

# In another terminal, test with curl:

# GET request
$ curl -v http://localhost:8080/index.html

# POST request with data
$ curl -X POST -H "Content-Type: application/x-www-form-urlencoded" \
       -d "name=value&foo=bar" http://localhost:8080/cgi-bin/script.php

# DELETE request
$ curl -X DELETE http://localhost:8080/uploads/file.txt

# Large file upload
$ curl -X POST -F "file=@bigfile.zip" http://localhost:8080/upload

# Multiple requests on same connection (keep-alive)
$ curl --keepalive-time 60 http://localhost:8080/file1 http://localhost:8080/file2

# Test with ab (Apache Bench)
$ ab -n 1000 -c 10 http://localhost:8080/
```

---

## Notes

- The server handles edge cases gracefully (malformed requests, incomplete uploads, client disconnects)
- HTTP error messages follow standard conventions
- Memory must be properly managed (no leaks)
- The program behaves as closely as possible to NGINX for compatibility
- Configuration file format follows NGINX conventions for familiarity
- CGI scripts execute in isolated child processes with proper environment setup
- Keep-alive connections are managed with configurable timeouts
