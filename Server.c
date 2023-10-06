// Weather update server
// Binds PUB socket to tcp://*:5556
// Publishes random weather updates

#include "zhelpers.h"
#include <stdio.h>

int main(void)
{
    // Prepare our context and publisher
    void *context = zmq_ctx_new();
    void *publisher = zmq_socket(context, ZMQ_PUB);
    int rc = zmq_bind(publisher, "tcp://*:5556");
    assert(rc == 0);

    // Initialize random number generator
    srandom((unsigned)time(NULL));
    while (1)
    {
        // Get values that will fool the boss
        int zipcode, temperature, relhumidity;
        zipcode = randof(100000);
        temperature = randof(125);
        relhumidity = randof(60);

        // Print the generated weather update
        //printf("Publishing weather update: %05d %d %d\n", zipcode, temperature, relhumidity);

        // Send message to all subscribers
        char update[20];
        sprintf(update, "%05d %d %d", zipcode, temperature, relhumidity);
        s_send(publisher, update);
    }

    zmq_close(publisher);
    zmq_ctx_destroy(context);
    return 0;
}
