//  Reading from multiple sockets
//  This version uses zmq_poll()
//  To actually read from multiple sockets all at once, use zmq_poll().

#include "zhelpers.h"

int main (void) 
{
    //  Connect to task ventilator
    void *context = zmq_ctx_new ();
    void *receiver = zmq_socket (context, ZMQ_PULL);
    zmq_connect (receiver, "tcp://localhost:5557");

    //  Connect to weather server
    void *subscriber = zmq_socket (context, ZMQ_SUB);
    zmq_connect (subscriber, "tcp://localhost:5556");
    zmq_setsockopt (subscriber, ZMQ_SUBSCRIBE, "10001 ", 6);

    zmq_pollitem_t items [] = {
        { receiver,   0, ZMQ_POLLIN, 0 },
        { subscriber, 0, ZMQ_POLLIN, 0 }
    };

    int iterations = 100;
    int total_temp = 0;
    //  Process messages from both sockets
    while (1) {
        char msg [256];

        zmq_poll (items, 2, -1); // is called to wait for events on the specified sockets
        if (items [0].revents & ZMQ_POLLIN) {
            int size = zmq_recv (receiver, msg, 255, 0);
            if (size != -1) {
                //  Process task
                printf("Received task: %.*s\n", size, msg);  // Print the task
                // Add your task processing logic here
            }
        }
        if (items [1].revents & ZMQ_POLLIN) {
            int size = zmq_recv (subscriber, msg, 255, 0);
            if (size != -1) {
                //  Process weather update

                int zipcode, temperature, relhumidity;
                sscanf(msg, "%d %d %d", &zipcode, &temperature, &relhumidity);

                // Print the received weather update
                printf("Received weather update: %05d %d %d\n", zipcode, temperature, relhumidity);

                total_temp += temperature; 
                iterations--;

                if (!iterations) {
                    printf("Average temperature for zipcode '%d' was %dF\n", zipcode, (int)(total_temp / 100)); // initially iterations = 100
                    break;
                }
                //break;
            }
        }
    }

    zmq_close (subscriber);
    zmq_ctx_destroy (context);

    return 0;
}

