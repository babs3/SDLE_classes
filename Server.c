//  Hello World server
#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>

const char* getWeatherForZipCode(const char* zipCode) {
    // This is a placeholder function. Replace this with your actual logic to get weather for the given zip code.
    // You can use external APIs or databases to fetch weather information based on zip codes.
    // Return a weather update based on the zip code provided.
    // For simplicity, we'll return a generic weather update here.
    if (strcmp(zipCode, "US123") == 0) {
        return "Weather in US: Sunny and clear skies.";
    } else if (strcmp(zipCode, "PT456") == 0) {
        return "Weather in PT: Rainy day.";
    } else {
        return "Unknown zip code.";
    }
}

int main (void)
{
    //  Socket to talk to clients
    void *context = zmq_ctx_new ();
    void *responder = zmq_socket (context, ZMQ_REP);
    int rc = zmq_bind (responder, "tcp://*:5555");
    assert (rc == 0);

    while (1) {
        //char buffer [10];
        char zipCode[6];  // 5-digit zip codes and null terminator

        //zmq_recv (responder, buffer, 10, 0);
        zmq_recv(responder, zipCode, 5, 0);

        //printf ("Received Hello\n");
        printf("Received zip code: %s\n", zipCode);

        // Get weather update based on the provided zip code
        const char* weatherUpdate = getWeatherForZipCode(zipCode);
        printf("Sending weather update: %s\n", weatherUpdate);
        
        sleep (1);          //  Do some 'work'
        
        //zmq_send (responder, "World", 5, 0);        
        zmq_send(responder, weatherUpdate, strlen(weatherUpdate), 0);
    }
    return 0;
}