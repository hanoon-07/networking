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

### udp1:

A multithreaded UDP-based chat system where:

- 🔁 Both client and server can **send and receive messages simultaneously** using `pthread`.
- 🧵 A separate **receive thread** continuously listens for incoming messages.
- 📤 `sendto()` is used to send messages and `recvfrom()` to receive them.
- 🖥️ Designed for **full-duplex chat** over UDP between two endpoints.

### timeserver:

A simple UDP-based time server where:

- ⏱️ Client sends `"get"` to the server requesting the current time.
- 🖥️ Server checks the message and replies with the **system time** using `ctime()`.
- 🔁 This process runs in a continuous loop for both server and client.
- 📡 Demonstrates time-based UDP communication using `sendto()` and `recvfrom()`.

### mutliuserchat:

A multi-client TCP chat application using threads, where:

- 💬 Clients connect to the server, provide their **name**, and start chatting.
- 📣 Server **broadcasts messages** from one client to all others using `send()`.
- 🧵 Each client is handled in a separate thread to allow simultaneous communication.
- 🔁 Client runs a listener thread to print incoming messages while sending new ones.

### fileserver:

A TCP-based file server that handles multiple clients using `fork()`:

- 📄 Client requests a **filename**; the server sends back the file contents line-by-line.
- 🔁 Server spawns a **new process** for each client using `fork()` (each with its own PID).
- ❌ If the file is not found, the server responds with an error message.
- 🔚 Transmission ends with a special marker (`__END__`) to indicate end of file.

### stopandwait:

A TCP-based simulation of the Stop-and-Wait ARQ protocol where:

- 📤 Client sends a sequence number (`int`) to the server.
- 🎲 Server randomly **simulates transmission success or failure** using `rand()`.
- 📨 If success, server replies with `'a'` (ACK); otherwise `'e'` (error).
- 🔁 Client only increments and sends next sequence number after receiving ACK, else it **resends** the same data.

### gobackn:

A TCP-based simulation of the **Go-Back-N ARQ protocol** where:

- 📤 Client sends data frames (`int`) in a window of size 5 to the server.
- 🎲 Server randomly simulates an **error** (`'e'`) or **acknowledgement** (`'a'`) using `rand()`.
- 🧠 If error occurs, client stores the failed sequence numbers and **resends them** in the next window.
- 🔁 Demonstrates the working of **Go-Back-N ARQ** with selective retransmission handling and window-based flow control.


### selective:

A TCP-based simulation of the **Selective Repeat ARQ protocol** where:

- 📦 Client sends frames in windows (size = 5), storing only failed transmissions.
- 🎯 On receiving `'e'` from the server, client **selectively retransmits** only the erroneous frames.
- 🧠 Successfully acknowledged frames (`'a'`) are not retransmitted — unlike Go-Back-N.
- 🔁 Mimics selective retransmission and out-of-order recovery behavior of Selective Repeat ARQ.




