# How can I run the program?

### To run Server
- first compile: `gcc -o Server Server.c -lzmq`
- then run `./Server`

### To run Client
- first compile: `gcc -o Client Client.c -lzmq`
- then run `./Client`

<br/>

# With the Makefile

- To compile and run the server: <br/>
`make Server 
./Server`

- To compile and run the client: <br/>
`make Client
./Client`