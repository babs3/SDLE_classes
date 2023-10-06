//  Weather update server
//  Binds PUB socket to tcp://*:5556
//  Publishes random weather updates

#include "zhelpers.h"

int main (void)
{
    //  Prepare our context and publisher
    void *context = zmq_ctx_new ();
    void *publisher = zmq_socket (context, ZMQ_PUB); // uses a PUB (publish) socket to publish updates
    int rc = zmq_bind (publisher, "tcp://*:5556"); // binds to the TCP address tcp://*:5556
    assert (rc == 0);

    //  Initialize random number generator
    srandom ((unsigned) time (NULL));
    while (1) {
        // The server generates random weather updates and publishes them to any connected subscribers
        int zipcode, temperature, relhumidity;
        zipcode     = randof (100000);
        temperature = randof (215) - 80;
        relhumidity = randof (50) + 10;

        //  Send message to all subscribers
        char update [20];
        sprintf (update, "%05d %d %d", zipcode, temperature, relhumidity); // The generated weather data is formatted into a string 
        s_send (publisher, update); // message sent to all subscribers
    }
    zmq_close (publisher);
    zmq_ctx_destroy (context);
    return 0;
}