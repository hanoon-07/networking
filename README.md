# 🔌 KTU Networking S6 Programs
## 📁 Contents
### udpchar:

- **Client sends:** a structure (`struct boo`) containing `name = "hanoon"` to the server.
- **Server receives:** the structure, extracts the `name` field, prints it to the console, and sends back a greeting message.
- **Client receives:** the response message `"hello from server\n"` and prints it.

### tcp:

A simple TCP client-server program where:

- The **client** sends a string to the server.
- The **server** reverses the string and sends it back.
- Communication ends when the client sends `"quit"`.

### tcpchar:

A TCP client-server program that:

- 📦 Client sends an array of structs (each with `rollno` and `name`) to the server.
- 🧑‍💻 Server receives one struct at a time and reads the `name` field.
- 💬 Server replies with a custom message like: `"the server says hi to <name>"`.
- 🔁 Client prints the response for each struct sent.

### pali:

A TCP client-server program where:

- 🧑‍💻 Client sends a string to the server.
- 🔁 Server checks if the string is a **palindrome** (same forward and backward).
- 📬 Server replies with `"true"` or `"false"` based on the result.
- 🛑 Typing `"quit"` ends the session.

###udp1:

## udpchatthreaded

A multithreaded UDP-based chat system where:

- 🔁 Both client and server can **send and receive messages simultaneously** using `pthread`.
- 🧵 A separate **receive thread** continuously listens for incoming messages.
- 📤 `sendto()` is used to send messages and `recvfrom()` to receive them.
- 🖥️ Designed for **full-duplex chat** over UDP between two endpoints.



