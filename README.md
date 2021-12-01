# TCP/IP Socket Client/Server
Implementation of a TCP client/server application, where the server is a remote computer that responds to client request in the following way: 
1. Once the connection is established, the client reads the operation to be performed (using the characters `+`,`x`, `-`,`/`, respectively for *Addition, Multiplication, Subtraction* and *Division*) and two integers from the standard input (e.g. `+ 23 45`) and sends what it has read from the keyboard to the server. 
2. The server reads what has been sent by the client, performs the requested operation and sends the result to the client (e.g. `68`). 
3. The client reads the answer sent by the server and visualizes it on the standard output. 
4. The client reads from the standard input the successive operation to complete. If instead of an operation the character `=` is inserted, the client closes the connection with the server and finishes its process here. Otherwise it returns to point 1.  
