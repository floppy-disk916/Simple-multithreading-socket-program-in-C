# Simple-multithreading-socket-program-in-C
```
Hello there!
```
Here's my simple windows API, multithreading socket program in C.
It's my first few moments of trying socket and threading with windows.h in C.
So yeah, still had some flaws here and there for now.
Not a production grade, though

It has some phases which i will describe below :
1. It will setup the windows socket API with `WSAStartup()`
2. It will create a socket with `socket()`
3. It will setup the server `sockaddr` struct member (`sin_family`, `sin_addr.s_addr`, `sin_port`)
   
Then from the server side :
a. It will bind the server port and server ip address with `bind()` function
b. `listen()`
c. `accept()`
d. `send()` greeting to the client

Then from the client side:
a. `connect()`

4. `CreateThread()` for `SendThread()`
5. `CreateThread()` for `ReceiveThread()`
6. `WaitforSingleObject()` for each thread to wait each until it's over
7. `CloseHandle()` each of the thread
8. `closesocket()` each of the socket
9. `WSACleanup()` to prevent resource leak
