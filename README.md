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
  <span><a href="#about-project" style="text-decoration:none; color:inherit;">About Project</a></span>
  &nbsp;•&nbsp;
  <span><a href="#mandatory-part" style="text-decoration:none; color:inherit;">Mandatory Part</a></span>
  &nbsp;•&nbsp;
  <span><a href="#bonus-part" style="text-decoration:none; color:inherit;">Bonus Part</a></span>
  &nbsp;•&nbsp;
  <span><a href="#usage" style="text-decoration:none; color:inherit;">Usage</a></span>
</div>

---

## <a name="about-project"></a>About Project

> 42 School WebServ project: Create your own HTTP server in C++98.
> Learn about network programming, the HTTP protocol, non-blocking I/O, and concurrent connection handling.

```
TL;DR: Build a web server from scratch.
- Listen for client connections on specified ports
- Parse HTTP requests and generate responses
- Serve static files and execute CGI scripts
- Handle multiple clients at the same time without threads
```

> [!NOTE]
> - C++98 standard required
> - Norminette compliant code
> - Only allowed functions from the subject
> - No external libraries (Boost forbidden)

**Contributors**: Sosonyx

---

## <a name="mandatory-part"></a>Mandatory Part

A **fully functional HTTP server** supporting:

### Core Features

- **HTTP Methods**: GET, POST, DELETE, HEAD
- **Static File Serving**: HTML, CSS, images, and other assets
- **Configuration File**: Define servers, ports, and locations (NGINX-like syntax)
- **Redirections**: HTTP 301/302 redirects as configured
- **Error Pages**: Custom error pages for common HTTP errors (404, 403, 500, etc.)
- **Non-Blocking I/O**: Single `poll()` call managing all connections
- **Connection Management**: Accept and handle multiple clients concurrently
- **File Uploads**: Accept POST requests with file uploads to specified directories
- **CGI Execution**: Run scripts (.py, .sh) based on file extensions

### Configuration Example

```nginx
server {
    listen 8080;
    name 127.0.0.1;
    client_body_max 500000;
    error_page 404 html/errors/404.html;
    
    location / {
        root html;
        index index.html;
        methods GET POST on DELETE off;
    }
    
    location /cgi {
        root cgi;
        cgi .py .sh;
        methods GET POST on;
    }
    
    location /upload {
        upload upload/pictures/;
        methods POST on;
    }
}
```

### Program Behavior

```
Server starts and reads configuration file.
Server binds to specified ports and listens for connections.
For each incoming request:
  - Parse HTTP headers and body
  - Determine which location matches the request
  - Execute the appropriate action (serve file, redirect, run CGI, etc.)
  - Send HTTP response back to client
Loop continues until server is shut down.
```

### Example Usage

```bash
$ ./webserv config/default.conf
# Server is now listening on ports defined in config

# In browser or another terminal:
$ curl http://127.0.0.1:8080/
$ curl -X POST -d "data" http://127.0.0.1:8080/
$ curl -X DELETE http://127.0.0.1:8080/file.html
$ curl -F "file=@image.png" http://127.0.0.1:8080/upload/
```

---

## <a name="bonus-part"></a>Bonus Part

Advanced features:

### Bonus Features

- **Session Management**: Store client data server-side with SessionId cookies
- **Theme System**: Dynamic theme switching (dark, white, yellow, horror) saved in sessions
- **Font System**: Multiple font options with session persistence
- **Keep-Alive Connections**: Reuse TCP connections for multiple requests
- **Multiple Virtual Hosts**: Different servers on same or different ports
- **Directory Listing**: Enable/disable directory browsing with autoindex
- **Cookie Support**: Full cookie parsing and persistence

### Example Bonus Usage

```bash
# Session with theme preference
$ curl -c cookies.txt -b cookies.txt \
  -X POST -d "username=Alice&theme=dark" \
  http://127.0.0.1:8080/

# File operations with different hosts
$ curl http://127.0.0.1:8080/              # Main server
$ curl http://127.0.0.1:8081/              # Alternative server
$ curl -X DELETE http://127.0.0.1:8081/file.html
```

---

## <a name="usage"></a>Usage

### Requirements

- C++ compiler with C++98 support
- Linux/Unix system
- GNU Make

### Compiling

```shell
$ cd path/to/webserv && make
```

### Running

```shell
$ ./webserv config/default.conf
# or just ./webserv if default path is set
```

### Testing

```shell
# Open in browser
$ open http://127.0.0.1:8080

# Test with curl
$ curl -v http://127.0.0.1:8080/
$ curl -X POST -d "test=data" http://127.0.0.1:8080/
$ curl -I http://127.0.0.1:8080/          # HEAD request
$ curl -X DELETE http://127.0.0.1:8080/deleteme.html

# Stress test
$ ab -n 100 -c 10 http://127.0.0.1:8080/
```

---

## Project Structure

```
webserv/
├── Makefile                    # Build configuration
├── config/                     # Configuration files
│   ├── default.conf
│   └── multipleServer.conf
├── includes/                   # Header files
│   ├── WebServer.hpp
│   ├── Server.hpp
│   ├── Connection.hpp
│   ├── Request.hpp
│   ├── Response.hpp
│   ├── ConfigParser.hpp
│   ├── Session.hpp
│   ├── Cgi.hpp
│   └── ...
├── srcs/                       # Source files
│   ├── main.cpp
│   ├── Server/
│   │   ├── WebServer.cpp
│   │   ├── Config/             # Configuration parsing
│   │   ├── Connections/        # Connection management
│   │   ├── RequestGestion/     # Request/Response handling
│   │   ├── CGI/                # CGI execution
│   │   └── Upload/             # File uploads
│   ├── exceptions/
│   ├── signal/
│   └── utils/
├── html/                       # Static website files
│   ├── index.html
│   ├── css/                    # Stylesheets
│   ├── errors/                 # Error pages
│   └── ...
├── cgi/                        # CGI scripts
│   ├── my_cgi.py
│   └── cgi.sh
└── upload/                     # Upload directory
```

---

## Non-Blocking I/O and Connection Handling

The core of WebServ is managing multiple client connections without using threads. This is done with **non-blocking sockets** and **I/O multiplexing** using `poll()`.

### The Concept

Instead of creating a new thread for each client, we use a single `poll()` call to monitor all sockets at once. When `poll()` returns, it tells us which sockets are ready for reading or writing. We then process only the ready sockets.

```
Main Loop:
1. Add all sockets to poll set
   - Server listening socket
   - All active client sockets
   - Any open CGI pipes

2. Call poll() - waits until something is ready
   - No CPU usage while waiting
   - Handles thousands of connections

3. When poll() returns, process ready sockets:
   - New connection? Accept it
   - Client has data? Read it
   - Client socket writable? Send response

4. Loop back to step 1
```

### Connection State Machine

Each client connection goes through a series of states. This ensures we process data in the correct order:

```
Accept connection
    ↓
BUFFERING: Receive request data from client
    ↓
PARSING: Parse HTTP headers and body
    ↓
WRITING: Process request (serve file, run CGI, etc.)
    ↓
SENDING: Send response back to client
    ↓
Keep-Alive? → YES → BUFFERING (next request)
           → NO  → Close connection
```

Each state is processed only when the socket is ready (determined by `poll()`). For example, we only call `recv()` if `poll()` says data is waiting, and we only call `send()` if the socket is writable.

### Why This Works

- No threads = no synchronization problems
- One process handles thousands of clients
- Fair scheduling - everyone gets a turn
- Scales much better than thread-per-client
- Uses much less memory

---

## Key Concepts

### HTTP Protocol

The server understands HTTP requests like:

```
GET /index.html HTTP/1.1
Host: localhost
Connection: keep-alive

```

And generates responses like:

```
HTTP/1.1 200 OK
Content-Type: text/html
Content-Length: 1234
Connection: keep-alive

<html>...</html>
```

### Sessions and Cookies

When a client connects, the server can create a session:
- Server generates a unique SessionId
- Sends it to client via Set-Cookie header
- Client sends it back with each request via Cookie header
- Server looks up session data server-side

This allows the server to remember information about each client without storing it in files or the client.

### Configuration

The server reads a configuration file on startup. This file defines:
- Which ports to listen on
- Where to find files (root directory)
- Which error pages to use
- Which HTTP methods are allowed
- Where to save uploaded files
- Which files to run as CGI scripts

This allows you to run multiple servers in one process, each with different settings.

---

## Learning Outcomes

- Understanding **sockets** and network communication
- **HTTP protocol** implementation
- **Non-blocking I/O** and multiplexing
- **Process management** (fork, execve for CGI)
- **State machines** for protocol handling
- **Configuration parsing** and server setup
- **Memory management** and cleanup
- **C++98** and object-oriented design

---

## Notes

- The server must handle client disconnections gracefully
- All sockets are non-blocking; we never block on I/O
- Configuration syntax is similar to NGINX for familiarity
- Error messages should be helpful and follow HTTP conventions
- Sessions expire and are cleaned up to prevent memory leaks
