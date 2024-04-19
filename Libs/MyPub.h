#include "D:\Projects\C++\App1\Libs\Mosquitto\devel\mosquitto.h"
#include <iostream>
void message_callback(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message) {
    // Handle received message here
    // You can access the message content using message->payload and message->payloadlen
     fprintf(stderr, "Error: Out of memory.\n");
}

int Start() {
    struct mosquitto *mosq = NULL;
    const char *host = "localhost";
    int port = 1883;
    int keepalive = 60;

    mosquitto_lib_init();

    mosq = mosquitto_new(NULL, true, NULL);
    if (!mosq) {
        fprintf(stderr, "Error: Out of memory.\n");
        return 1;
    }

    mosquitto_message_callback_set(mosq, message_callback);

    if (mosquitto_connect(mosq, host, port, keepalive) != MOSQ_ERR_SUCCESS) {
        fprintf(stderr, "Unable to connect to the MQTT broker.\n");
        return 1;
    }

    if (mosquitto_subscribe(mosq, NULL, "topic", 0) != MOSQ_ERR_SUCCESS) {
        fprintf(stderr, "Unable to subscribe to the topic.\n");
        return 1;
    }

    mosquitto_loop_forever(mosq, -1, 1);

    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();

    return 0;
}