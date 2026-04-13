# WebServ - HTTP Server

<div align="center">

 For further information about 42cursus and its projects, see <a href="https://42.fr/le-campus-de-paris/diplome-informatique/"><b>42school</b></a>.
 <p>
    <img src="https://img.shields.io/badge/language-C-blue?style=for-the-badge" />
    <img src="https://img.shields.io/github/repo-size/Sosonyx/minishell?style=for-the-badge&logo=github">
    <img src="https://img.shields.io/github/languages/count/Sosonyx/minishell?style=for-the-badge" />
    <img src="https://img.shields.io/github/languages/top/Sosonyx/minishell?style=for-the-badge" />
    <img src="https://img.shields.io/github/last-commit/Sosonyx/minishell?style=for-the-badge" />
  </p>
</div>

---

Contributors: @theofiette, @Thermow

## 📜 Description

WebServ is a from-scratch implementation of an **HTTP/1.1 web server** written in **C++98**. This project demonstrates a deep understanding of network programming, the HTTP protocol, non-blocking I/O multiplexing, and concurrent connection management.

The server is production-oriented with features including:
- **Non-blocking socket architecture** using `poll()` for I/O multiplexing
- **Session management** with cookie-based SessionId tracking
- **Dynamic theme and font switching** via client-side cookies
- **CGI script execution** (Python, Bash, etc.)
- **File upload handling**
- **Multiple virtual servers** on different ports with independent configurations
- **State machine-based connection handling** for robust request processing

You can open the website directly in your browser at `http://127.0.0.1:8080` and interact with a fully functional web interface.

---

## 🚀 Features

### Core HTTP Features

| Feature | Status | Description |
|---------|:------:|-------------|
| **GET Method** | ✅ | Retrieve files and resources |
| **POST Method** | ✅ | Submit forms and upload files |
| **DELETE Method** | ✅ | Remove resources from server |
| **HEAD Method** | ✅ | Retrieve headers without body |
| **HTTP/1.1 Protocol** | ✅ | Full HTTP/1.1 compliance |
| **Keep-Alive** | ✅ | Persistent connections (configurable) |
| **Static File Serving** | ✅ | HTML, CSS, JavaScript, images, etc. |
| **Error Pages** | ✅ | Custom error pages (404, 403, 500, etc.) |
| **Redirections** | ✅ | HTTP 301/302/307/308 redirects |

### Advanced Features

| Feature | Status | Description |
|---------|:------:|-------------|
| **Sessions** | ✅ | ServerSide session management via SessionId cookie |
| **Theme System** | ✅ | Dynamic theme switching (dark, white, yellow, horror, etc.) |
| **Font System** | ✅ | Multiple font options (arial, horror, etc.) |
| **Cookie Support** | ✅ | Full cookie parsing and management |
| **CGI Execution** | ✅ | Run CGI scripts (.py, .sh, .cgi, .out) |
| **File Upload** | ✅ | Configurable upload directories and limits |
| **Virtual Hosts** | ✅ | Multiple servers on different ports |
| **Non-Blocking I/O** | ✅ | Single poll() for all I/O operations |
| **Connection Timeouts** | ✅ | Configurable request and CGI timeouts |
| **Directory Listing** | ✅ | Autoindex for directory browsing |

---

## 📋 Requirements

- **C++ Compiler**: GCC/Clang with C++98 support
- **Language Standard**: C++98 (compiles with `-std=c++98` flag)
- **Build Tool**: GNU Make
- **System**: Unix/Linux (tested on Linux)
- **Compilation Flags**: `-Wall -Wextra -Werror -std=c++98`

### Dependencies

No external libraries or Boost allowed. All functionality implemented from scratch using POSIX APIs:
- `poll()` - I/O multiplexing
- `socket()`, `bind()`, `listen()`, `accept()` - Socket operations
- `fork()`, `execve()` - CGI execution (process management)
- `select()` alternative to `poll()` is supported
- `fcntl()` on macOS for non-blocking mode

---

## 📦 Installation & Compilation

### Clone and Build

```bash
$ git clone <repository_url> webserv
$ cd webserv
$ make
```

The executable `webserv` will be created in the project root.

### Build Rules

```bash
$ make              # Build the project
$ make clean        # Remove object files
$ make fclean       # Remove all generated files
$ make re           # Rebuild from scratch
```

---

## 🎯 Usage

### Running the Server

```bash
# Using default configuration file (config/default.conf)
$ ./webserv

# Using custom configuration file
$ ./webserv config/multipleServer.conf
```

The server will start listening on the ports defined in the configuration file (default: port 8080).

### Accessing the Server

**In your browser:**
```
http://127.0.0.1:8080
http://127.0.0.1:8081
```

**Via command line:**
```bash
# GET request
$ curl http://127.0.0.1:8080/

# POST form submission
$ curl -X POST -d "username=John&theme=dark" http://127.0.0.1:8080/

# HEAD request (headers only)
$ curl -I http://127.0.0.1:8080/

# DELETE file
$ curl -X DELETE http://127.0.0.1:8080/todelete/file1.html

# Upload file
$ curl -F "file=@image.png" http://127.0.0.1:8080/upload/
```

### Example Browser Interaction

1. **Navigate to** `http://127.0.0.1:8080/`
2. **Submit your username** via the POST form
3. A session is created with a `SessionId` cookie stored server-side
4. **Switch themes** (dark, white, yellow, horror) - preference saved in session
5. **Select fonts** (arial, horror) - preference saved in session
6. **Upload files** to `http://127.0.0.1:8080/upload/`
7. **View uploaded files** and delete them if allowed

---

## ⚙️ Configuration File

The server uses a **NGINX-inspired configuration format**. Multiple servers can be defined, each listening on specific ports with independent settings.

### Configuration Structure

```nginx
# Global settings
max_clients 1024;

global {
    location_cookie      off;      # Global cookie handling
    location_method      on;       # Method restriction support
    location_root        html;     # Default root directory
    location_index       index.html; # Default index file
    location_autoindex   on;       # Directory listing
    redir_valid          off;      # Validate redirects
    redir_errorcode      301;      # Default redirect code
    redir_path           /index.html; # Redirect path
}

# Server 1: Main server with full features
server {
    listen               8080;
    name                 127.0.0.1;
    client_body_max      500000;   # Max upload size (500KB)
    
    # Error pages
    error_page           html/errors/error.html;
    error_page 404       html/errors/404_error.html;
    error_page 403       html/errors/403_error.html;
    
    # Root location - serves static files
    location / {
        root             html;
        index            index.html;
        upload           upload/pictures/;
        methods          GET POST on DELETE off;
    }
    
    # CGI location - execute scripts
    location /cgi {
        root             cgi;
        index            my_cgi.py;
        cgi              .py .sh .cgi .out;
        methods          GET POST on DELETE off;
    }
    
    # Style location - serve CSS with session cookies
    location /style {
        root             html/css/style;
        index            style.css;
        cookie           on;
        methods          GET POST on DELETE off;
    }
    
    # Theme location - theme switcher
    location /theme {
        root             html/css/style/theme;
        index            theme.css;
        cookie           on;
        methods          GET POST on DELETE off;
    }
    
    # Font location - font switcher
    location /font {
        root             html/css/style/font;
        index            font.css;
        cookie           on;
        methods          GET POST on DELETE off;
    }
}

# Server 2: Restricted methods server
server {
    listen               8080;
    name                 127.0.0.2;
    client_body_max      200000;
    
    location / {
        root             html;
        index            methods.html;
        methods          GET on POST off DELETE off;
    }
    
    location /upload {
        root             html;
        upload           upload/pictures/;
        methods          POST on GET off DELETE off;
    }
}

# Server 3: DELETE-enabled server
server {
    listen               8081;
    name                 127.0.0.3;
    client_body_max      300000;
    
    location / {
        root             html;
        index            post.html;
        methods          GET POST on DELETE off;
    }
    
    location /todelete {
        root             html;
        autoindex        on;
        methods          DELETE on;
    }
}
```

### Configuration Parameters

#### Server-Level
- `listen PORT` - Port to listen on
- `name HOST` - Server name/host binding
- `client_body_max SIZE` - Maximum request body size in bytes
- `error_page [CODE] FILE` - Error page file path

#### Location-Level
- `root PATH` - Root directory for this location
- `index FILE` - Default file to serve
- `upload DIR` - Directory for file uploads
- `methods METHOD on/off` - HTTP methods (GET, POST, DELETE, HEAD)
- `cgi .EXT` - CGI extensions to execute
- `cookie on/off` - Enable cookie support for this location
- `autoindex on/off` - Directory listing

---

## 🏗️ Architecture

### Project Structure

```
webserv/
├── Makefile                          # Build configuration
├── webserv                           # Compiled executable
├── config/                           # Configuration files
│   ├── default.conf                  # Default server config
│   ├── multipleServer.conf           # Multi-server example
│   └── supression.supp               # Valgrind suppressions
├── includes/                         # Header files
│   ├── WebServer.hpp                 # Main server class
│   ├── Server.hpp                    # Individual server
│   ├── Connection.hpp                # Connection state machine
│   ├── ConnectionManager.hpp         # Connection manager
│   ├── Request.hpp                   # HTTP request parsing
│   ├── Response.hpp                  # HTTP response generation
│   ├── Cgi.hpp                       # CGI execution
│   ├── ConfigParser.hpp              # Config file parser
│   ├── Session.hpp                   # Session management
│   ├── SessionManager.hpp            # Session registry
│   ├── Location.hpp                  # Location configuration
│   ├── UploadHandler.hpp             # File upload handling
│   └── ...
├── srcs/                             # Source files
│   ├── main.cpp                      # Entry point
│   ├── Server/
│   │   ├── WebServer.cpp             # Main server loop
│   │   ├── Config/
│   │   │   ├── ConfigParser.cpp      # Parse config files
│   │   │   ├── Server.cpp            # Server configuration
│   │   │   ├── Location.cpp          # Location configuration
│   │   │   └── Redir.cpp             # Redirection handling
│   │   ├── Connections/
│   │   │   ├── ConnectionManager.cpp # Manage all connections
│   │   │   └── Connection.cpp        # Individual connection (state machine)
│   │   ├── RequestGestion/
│   │   │   ├── Request.cpp           # Parse HTTP requests
│   │   │   ├── Response.cpp          # Build HTTP responses
│   │   │   ├── Session.cpp           # Session data
│   │   │   └── SessionManager.cpp    # Session registry
│   │   ├── CGI/
│   │   │   └── Cgi.cpp               # Execute CGI scripts
│   │   ├── Upload/
│   │   │   └── UploadHandler.cpp     # Handle file uploads
│   │   └── Helpers/Time/
│   │       └── TimeoutTracker.cpp    # Request timeouts
│   ├── exceptions/
│   │   └── exceptions.cpp            # Custom exceptions
│   ├── signal/
│   │   └── signal.cpp                # Signal handling
│   └── utils/
│       ├── wrapper.cpp               # Function wrappers
│       ├── format.cpp                # String formatting
│       └── safemath.cpp              # Safe math operations
├── html/                             # Static website files
│   ├── index.html                    # Home page with session demo
│   ├── session.html                  # Session information page
│   ├── post.html                     # POST form example
│   ├── upload.html                   # File upload form
│   ├── delete.html                   # DELETE form example
│   ├── cookies.html                  # Cookie demo
│   ├── cgi.html                      # CGI execution example
│   ├── methods.html                  # HTTP methods reference
│   ├── get.html                      # GET example
│   ├── success.html                  # Success page
│   ├── css/
│   │   └── style/
│   │       ├── style.css             # Main stylesheet
│   │       ├── theme/                # Theme files
│   │       │   ├── dark.css          # Dark theme
│   │       │   ├── white.css         # Light theme
│   │       │   ├── yellow.css        # Yellow theme
│   │       │   ├── horror.css        # Horror theme
│   │       │   └── theme.css         # Default theme
│   │       └── font/                 # Font files
│   │           ├── arial.css         # Arial font
│   │           ├── horror.css        # Horror font
│   │           └── font.css          # Default font
│   ├── medias/images/                # Images
│   ├── errors/                       # Error pages
│   │   ├── 404_error.html
│   │   ├── 403_error.html
│   │   ├── 415_error.html
│   │   ├── 500_error.html
│   │   └── error.html
│   └── todelete/                     # Test files for DELETE
├── cgi/                              # CGI scripts
│   ├── my_cgi.py                     # Python CGI example
│   ├── cgi.sh                        # Bash CGI example
│   └── SessionProofCGI.sh            # Session proof CGI
└── upload/pictures/                  # Upload directory
```

### Connection State Machine

The core of the server is a **robust state machine** that manages each connection through its lifecycle:

```
┌─────────────────────────────────────────────────────────────────┐
│                    CONNECTION STATE MACHINE                     │
└─────────────────────────────────────────────────────────────────┘

                              ┌─────────────┐
                              │   CS_NONE   │ ← Connection accepted
                              └──────┬──────┘
                                     │ (POLLIN + data available)
                                     ▼
                              ┌──────────────────┐
                              │  CS_BUFFERING    │ ← Receive request chunks
                              └──────┬───────────┘
                                     │ (Complete request received)
                                     ▼
                              ┌──────────────────┐
                              │  CS_PARSING      │ ← Parse HTTP headers
                              └──────┬───────────┘
                                     │ (Headers parsed)
                                     ▼
                              ┌──────────────────┐
                              │  CS_WRITING      │ ← Process request
                              └──────┬───────────┘
                                     │
                        ┌────────────┴──────────────┐
                        │                           │
                  (Is CGI?)                    (Not CGI)
                        │                           │
                        ▼                           ▼
              ┌───────────────────┐      ┌──────────────────┐
              │  CS_LAUNCH_CGI    │      │  CS_SENDING      │ ← Send response
              └─────────┬─────────┘      └──────┬───────────┘
                        │                       │ (POLLOUT + writable)
                        ▼                       ▼
              ┌───────────────────┐
              │   CS_WAIT_CGI     │ ← Wait for CGI output
              └─────────┬─────────┘
                        │ (CGI done)
                        ▼
              ┌───────────────────┐
              │   CS_SENDING      │ ← Send CGI response
              └─────────┬─────────┘
                        │ (Response sent)
                        ▼
                  ┌──────────────┐
                  │   CS_KEEP    │ ← Keep-alive or close?
                  └──────┬───────┘
                         │
            ┌────────────┴────────────┐
            │                         │
      (Keep-Alive)            (Close connection)
            │                         │
            ▼                         ▼
        CS_NONE ──────────→ ┌─────────────────┐
                            │   CS_CLOSE      │
                            └─────────────────┘
                                     │
                                     ▼
                            (Connection destroyed)

States:
- CS_NONE       : Initial state, waiting for data
- CS_BUFFERING  : Receiving request data from client
- CS_PARSING    : Parsing HTTP request headers
- CS_WRITING    : Processing request, preparing response
- CS_LAUNCH_CGI : Fork and execute CGI script
- CS_WAIT_CGI   : Wait for CGI output via pipe
- CS_SENDING    : Sending response to client
- CS_KEEP       : Deciding keep-alive vs close
- CS_CLOSE      : Cleanup and connection termination
```

### Non-Blocking I/O Architecture

The server uses **single `poll()` call** to manage all I/O operations:

```cpp
// Main event loop (simplified)
while (server_running) {
    // Add all sockets to poll set
    std::vector<pollfd> fds;
    
    for (Server &srv : servers) {
        fds.push_back({srv.listen_fd, POLLIN, 0});  // Listen socket
        
        // Each connection's fd (or CGI pipe if waiting)
        for (Connection &conn : srv.connections) {
            fds.push_back({
                conn.getPollFd(),        // Socket or CGI pipe
                conn.getWantedEvent(),   // POLLIN or POLLOUT
                0
            });
        }
    }
    
    // Single poll call for all I/O
    int activity = poll(fds.data(), fds.size(), timeout_ms);
    
    if (activity > 0) {
        // Process all ready file descriptors
        for (pollfd &pf : fds) {
            if (pf.revents == 0) continue;
            
            // Handle listen socket (new connection)
            // or process existing connection
        }
    }
}
```

**Key Benefits:**
- ✅ Scales to thousands of concurrent connections
- ✅ CPU efficient (no busy-waiting)
- ✅ Fair scheduling between connections
- ✅ Single-threaded, no synchronization needed

### Session Management

Sessions are managed **server-side** with client-side **cookie-based SessionId**:

```cpp
// Client receives SessionId cookie
// Server stores session data internally
SessionManager::accessSession("SessionId_ABC123", serverId);
→ Returns Session* with user data

// Session expires after configurable timeout
// Old sessions are garbage collected
```

The session system enables:
- **Theme preference persistence** (dark, white, yellow, horror)
- **Font preference persistence** (arial, horror)
- **User data tracking** (username from POST form)
- **Cross-request state** without modifying client-side files

---

## 🧪 Testing

### Browser Testing

Simply open your browser and navigate to:
```
http://127.0.0.1:8080/
```

The web interface allows you to:
- Submit a POST form with your username
- Switch themes and fonts (saved in session)
- Upload and download files
- View CGI output
- Test DELETE functionality
- Inspect cookies and session data

### Command-Line Testing

```bash
# Test GET request
$ curl -v http://127.0.0.1:8080/

# Test HEAD request (no body)
$ curl -I http://127.0.0.1:8080/

# Test POST with session
$ curl -v -c cookies.txt -b cookies.txt \
  -X POST -d "username=Alice&theme=dark" \
  http://127.0.0.1:8080/

# Test file upload
$ curl -F "file=@myimage.png" http://127.0.0.1:8080/upload/

# Test DELETE
$ curl -X DELETE http://127.0.0.1:8081/todelete/file1.html

# Test CGI execution
$ curl http://127.0.0.1:8080/cgi

# Stress test with Apache Bench
$ ab -n 1000 -c 10 http://127.0.0.1:8080/
```

### Telnet Testing

```bash
# Manual HTTP request
$ telnet 127.0.0.1 8080
Trying 127.0.0.1...
Connected to 127.0.0.1.
Escape character is '^]'.

GET / HTTP/1.1
Host: localhost
Connection: close

HTTP/1.1 200 OK
Content-Length: 1234
Content-Type: text/html

[response body...]
```

---

## 🔧 Key Implementation Details

### Non-Blocking Mode

All sockets are set to non-blocking mode:
```cpp
fcntl(socket_fd, F_SETFL, O_NONBLOCK);  // On macOS
// Or implicit in recv/send with poll readiness check
```

### Timeout Management

- **Request timeout**: Configurable per connection
- **CGI timeout**: Prevent hung CGI scripts
- **Keep-alive timeout**: Allow connection reuse with limits

### Error Handling

- **HTTP error pages**: Custom pages for 404, 403, 500, etc.
- **Graceful degradation**: Malformed requests handled safely
- **Resource limits**: Max clients, body size, connection limits

### Memory Management

- No memory leaks (tested with Valgrind)
- Proper cleanup on connection close
- Session garbage collection for expired sessions
- Safe string and pointer operations throughout

---

## 📚 Resources

### HTTP References
- [HTTP/1.1 RFC 7230-7235](https://tools.ietf.org/html/rfc7230)
- [HTTP/1.0 RFC 1945](https://tools.ietf.org/html/rfc1945)
- [NGINX Documentation](https://nginx.org/en/docs/)
- [MDN: HTTP Protocol](https://developer.mozilla.org/en-US/docs/Web/HTTP)

### System Programming
- [POSIX Poll](https://man7.org/linux/man-pages/man2/poll.2.html)
- [Socket Programming](https://man7.org/linux/man-pages/man2/socket.2.html)
- [Fork and Execve](https://man7.org/linux/man-pages/man2/fork.2.html)
- [Signals](https://man7.org/linux/man-pages/man7/signal.7.html)

### CGI References
- [CGI RFC 3875](https://tools.ietf.org/html/rfc3875)
- [CGI Environment Variables](https://en.wikipedia.org/wiki/Common_Gateway_Interface)

### C++ References
- [C++98 Standard](https://en.cppreference.com/)
- [STL Documentation](https://en.cppreference.com/w/cpp)

---

## 🎓 Learning Outcomes

This project demonstrates mastery of:

✅ **Network Programming**
- Socket creation, binding, listening, accepting
- Non-blocking I/O and multiplexing (`poll()`, `select()`)
- TCP/IP protocol stack
- Connection lifecycle management

✅ **HTTP Protocol**
- HTTP/1.1 request/response parsing
- Header processing and validation
- Status codes and error handling
- Keep-alive connections

✅ **Concurrent Programming**
- State machine design for concurrent operations
- Race condition avoidance without threads
- Fair scheduling of multiple connections
- Timeout and resource management

✅ **System Programming**
- Process management (`fork()`, `execve()`, `waitpid()`)
- File descriptor management (pipes, sockets)
- Signal handling (SIGCHLD, SIGINT)
- File I/O and directory operations

✅ **Software Engineering**
- Clean architecture with separation of concerns
- Robust error handling and edge cases
- Configuration file parsing
- Stress testing and optimization

✅ **C++ Programming**
- Object-oriented design with classes
- Standard library usage (STL containers)
- Memory management and RAII
- C++98 compliance without modern features

---

## 📝 Notes

- The server passes **strict compilation checks** with `-Wall -Wextra -Werror -std=c++98`
- All functionality is implemented in **C++98** without external libraries
- The server is **production-ready** with proper error handling and timeouts
- Configuration is **NGINX-inspired** for familiarity and power
- The code includes **comprehensive comments** for educational value
- Tested with **modern browsers** and **command-line tools**

---

## 📄 License

This project is part of the 42 curriculum and follows the school's guidelines.
