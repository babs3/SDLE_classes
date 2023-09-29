//  Hello World client
#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main (void)
{
    printf("Connecting to weather update servers...\n");

    void *context = zmq_ctx_new ();

    //void *requester = zmq_socket (context, ZMQ_REQ);
    //zmq_connect (requester, "tcp://localhost:5555");
    
    // Connect to US weather update server
    void *requesterUS = zmq_socket (context, ZMQ_REQ);
    zmq_connect (requesterUS, "tcp://localhost:5555");

    // Connect to PT weather update server
    void *requesterPT = zmq_socket(context, ZMQ_REQ);
    zmq_connect(requesterPT, "tcp://localhost:5555");

    int request_nbr;
    for (request_nbr = 0; request_nbr != 10; request_nbr++) {
        /*char buffer [10];
        printf ("Sending Hello %d…\n", request_nbr);
        zmq_send (requester, "Hello", 5, 0);
        zmq_recv (requester, buffer, 10, 0);
        printf ("Received World %d\n", request_nbr);*/

       if (request_nbr % 2 == 0) {
            // Send US zip code
            printf("Sending US zip code\n");
            zmq_send(requesterUS, "US123", 6, 0);

            char buffer[256];
            zmq_recv(requesterUS, buffer, sizeof(buffer), 0);
            printf("Received from US publisher: %s\n", buffer);
        } else {
            // Send PT zip code
            printf("Sending PT zip code\n");
            zmq_send(requesterPT, "PT456", 6, 0);

            char buffer[256];
            zmq_recv(requesterPT, buffer, sizeof(buffer), 0);
            printf("Received from PT publisher: %s\n", buffer);
        }

    }

    //zmq_close (requester);
    zmq_close(requesterUS);
    zmq_close(requesterPT);
    zmq_ctx_destroy (context);

    return 0;
}