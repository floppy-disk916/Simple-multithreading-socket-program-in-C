# Simple-multithreading-socket-program-in-C
```
Hello there!
```
Here's my simple windows API, multithreading socket program in C
It's my first few moments of trying socket and threading with windows.h in C.
So yeah, still had some flaws here and there for now
Not a production grade, though

It has some phases which i will describe below :
1. It will setup the windows socket API with `WSAStartup()`. Then, the value got checked with value `0` which is an error value of `WSAStartup()`
2. It will create a socket with `socket()`
3. It will setup the server `sockaddr` struct member (`sin_family`, `sin_addr.s_addr`, `sin_port`)
   
Then for server side :
4. It will bind the server port and server ip address with `bind()` function
5. 
