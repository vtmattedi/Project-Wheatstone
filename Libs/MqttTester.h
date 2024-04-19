#include <C:\Program Files\mosquitto\devel\mosquitto.h>
#include <stdio.h>

void connect_callback(struct mosquitto *mosq, void *obj, int result) {
    printf("connect callback, rc=%d\n", result);
}

void message_callback(struct mosquitto *mosq, void *obj, const struct mosquitto_message *message) {
    printf("got message '%.*s' for topic '%s'\n", message->payloadlen, (char*) message->payload, message->topic);
}

int Start() {
    struct mosquitto *mosq;
    int rc = 0;

    mosquitto_lib_init();

    mosq = mosquitto_new(NULL, true, NULL);
    if(!mosq){
        printf("Error: Out of memory.\n");
        return 1;
    }

    mosquitto_connect_callback_set(mosq, connect_callback);
    mosquitto_message_callback_set(mosq, message_callback);

    rc = mosquitto_connect(mosq, "localhost", 1883, 60);
    if(rc){
        printf("Could not connect to Broker with return code %d\n", rc);
        return rc;
    }

    mosquitto_subscribe(mosq, NULL, "test/topic", 0);

    while(true){
        rc = mosquitto_loop(mosq, -1, 1);
        if(rc){
            printf("connection error!\n");
            //_sleep(10);
            mosquitto_reconnect(mosq);
        }
    }

    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();

    return rc;
}