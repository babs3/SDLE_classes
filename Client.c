//  Reading from multiple sockets
//  This version uses a simple recv loop

/* The cost of this approach is some additional latency on the first message (the sleep 
* at the end of the loop, when there are no waiting messages to process). 
* This would be a problem in applications where submillisecond latency was vital. 
*/


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

    int iterations = 100;
    int total_temp = 0;
    //  Process messages from both sockets
    //  We prioritize traffic from the task ventilator
    while (1) {
        char msg [256];
        while (1) {
            int size = zmq_recv (receiver, msg, 255, ZMQ_DONTWAIT);
            if (size != -1) {
                //  Process task
                // don't know what to do here ...
            }
            else
                break;
        }
        while (1) {
            int size = zmq_recv (subscriber, msg, 255, ZMQ_DONTWAIT);
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

            }

            else
                break;
        }
        //  No activity, so sleep for 1 msec
        s_sleep (1);
        
        if (!iterations) break;

    }

    zmq_close (receiver);
    zmq_close (subscriber);
    zmq_ctx_destroy (context);

    return 0;
}