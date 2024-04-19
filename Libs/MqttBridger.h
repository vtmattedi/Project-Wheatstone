#include <iostream>
#include <C:\Program Files\mosquitto\devel\mosquitto.h>
#include <stdio.h>
#include <string.h>
#include <D:\Projects\C++\App1\Creds\HiveMQCred.h>
#include <list>
#include <map>
#define PROJECT_NAME "Wheatstone"

#include <D:\Projects\C++\App1\Libs\Logger.h>
#include <D:\Projects\C++\App1\Libs\Debugger.h>
#include <D:\Projects\C++\App1\Libs\TcpServer.h>
extern TcpServer server;
struct mosquitto *mqttHiveMq;
struct mosquitto *mqttLocal;

time_t Last_state_update = time(NULL);

int8_t mqtt_status_flags = 0;

const uint32_t HIVE_MQ_ID = 0x01;
const uint32_t LOCAL_ID = 0x02;
enum mqtt_status_flag
{
    MQTT_DISCONNECTED = 0,
    HIVEMQ_CONNECTED = HIVE_MQ_ID,
    LOCAL_CONNECTED = LOCAL_ID
};

void set_mqtt_status_flag(mqtt_status_flag flag, bool value)
{
    if (value)
    {
        mqtt_status_flags |= flag;
    }
    else
    {
        mqtt_status_flags &= ~flag;
    }
}

int localmq_total_messages = 0;
int hivemq_total_messages = 0;

Logger logger;
Debugger debugger;

// Commandline cmd;
bool enable_bridge = false;
bool print_router = false;

enum BridgeProtcol
{
    Qos = 1,
    BridgerQueue = 2,
    DontBridge = 4
};
BridgeProtcol bridgeProtocol = Qos;

struct customMessageId
{
    customMessageId(std::string topic, std::string message, int id)
    {
        this->topic = topic;
        this->message = message;
        this->id = id;
    }
    std::string topic;
    std::string message;
    int id;
};

/// @brief Only supports two mqtt servers.
struct bridger
{
    std::list<customMessageId> messages;

    /// @brief Process a message. If the message was sent by a different server, it will be sent to the other server. Otherwise it will be added to the queue.
    /// @param id Serve Id Only supports two mqtt servers.
    /// @param topic mqtt topic
    /// @param message mqtt message
    /// @return True if you should send the message to the other server. False if the message is a copy of what you sent.
    bool process(int id, std::string topic, std::string message)
    {
        bool found = false;
        // for (customMessageId msg : messages)
        // {
        //     if (msg.id != id && msg.topic == topic && msg.message == message)
        //     {
        //         found = true;
        //         messages.remove(msg);
        //     }
        // }
        if (found)
            return false;
        messages.push_back(customMessageId(topic, message, id));
        return true;
    }
} BridgerQ;

enum deviceSource
{
    UNDEFINED = 0,
    HIVEMQ = HIVE_MQ_ID,
    LOCAL = LOCAL_ID,
    BOTH = HIVE_MQ_ID | LOCAL_ID,
    TCP = 0xf0
};

std::string deviceSourceToString(deviceSource source)
{
    switch (source)
    {
    case LOCAL:
        return "LOCAL";
    case HIVEMQ:
        return "HIVEMQ";
    case BOTH:
        return "BOTH";
    case TCP:
        return "TCP";
    default:
        return "UNKNOWN";
    }
}

class DeviceCounter
{
public:
    bool debug = false;
    std::map<std::string, deviceSource> devices;
    void addDeviceFromBridge(std::string topic, deviceSource source)
    {

        std::string device = topic;
        int slash = device.find("/state");
        if (slash != std::string::npos)
        {
            device = device.substr(0, slash);
            updateDevice(device, source);
            if (debug)
            {
                printf("Device: %s Source: %s. Topic was: '%s'.\n", device.c_str(), deviceSourceToString(source).c_str(), topic.c_str());
            }
        }
    }
    void updateDevice(std::string device, deviceSource value)
    {
        devices[device] = value;
    }

    DeviceCounter()
    {
        devices = std::map<std::string, deviceSource>();
    }
} MqttDevices;

const char *get_id_name(uint32_t id)
{
    if (id == HIVE_MQ_ID)
    {
        return "HiveMQ";
    }
    else if (id == LOCAL_ID)
    {
        return "Local";
    }
    else
    {
        return "Unknown";
    }
}

deviceSource getDeviceSource()
{
    switch (mqtt_status_flags)
    {
    case MQTT_DISCONNECTED:
        return UNDEFINED;
    case HIVEMQ_CONNECTED:
        return HIVEMQ;
    case LOCAL_CONNECTED:
        return LOCAL;
    case HIVEMQ_CONNECTED | LOCAL_CONNECTED:
        return BOTH;
    default:
        return UNDEFINED;
    }
}

/// @brief publish state to both mqtt servers. -> online/offline
/// publish stauts to both mqtt servers. -> local/hive/both
void publish_state()
{
    std::string status = std::to_string(mqtt_status_flags); 
    mosquitto_publish(mqttHiveMq, NULL, "Wheatstone/status", status.size(), status.c_str(), 2, true);
    mosquitto_publish(mqttLocal, NULL, "Wheatstone/status", status.size(), status.c_str(), 2, true);

    /// @brief publish state to both mqtt servers.???
    mosquitto_publish(mqttHiveMq, NULL, "Wheatstone/state", 6, "online", 2, true);
    mosquitto_publish(mqttLocal, NULL, "Wheatstone/state", 6, "online", 2, true);

}

void connect_callback(struct mosquitto *mosq, void *obj, int result)
{
    int id = *(uint32_t *)obj;

    printf("[%s] [%s] connect callback, rc=%d\n", getCurrentTime().c_str(), get_id_name(id), result);

    if (id == HIVE_MQ_ID)
    {
        mosquitto_subscribe(mqttHiveMq, NULL, "#", 2);
        mosquitto_publish(mqttHiveMq, NULL, "Wheatstone/state", 6, "online", 2, true);
        set_mqtt_status_flag(HIVEMQ_CONNECTED, true);
    }
    else if (id == LOCAL_ID)
    {
        mosquitto_subscribe(mqttLocal, NULL, "#", 2);
        mosquitto_publish(mqttLocal, NULL, "Wheatstone/state", 6, "online", 2, true);
        set_mqtt_status_flag(LOCAL_CONNECTED, true);
    }
    MqttDevices.updateDevice("Wheatstone (this)", getDeviceSource());
}

void message_callback(struct mosquitto *mosq, void *obj, const struct mosquitto_message *message)
{
    if (!message->payloadlen)
    {
        return;
    }

    int id = *(uint32_t *)obj;

    if (message->topic == "All/control")
    {
        if (message->payload == "get_state")
        {
        
        }
        
    }
    

    if (message->topic == "Wheatstone/status" || message->topic == "Wheatstone/state" || message->topic == "Wheatstone/bridge" || message->topic == "Wheatstone/bridge/protocol" || message->topic == "Wheatstone/bridge/protocol" || message->topic == "Wheatstone/bridge/protocol")
    {
        if (message->topic == "Wheatstone/bridge/protocol")
        {
            if (strcmp((char *)message->payload, "qos") == 0)
            {
                bridgeProtocol = Qos;
            }
            else if (strcmp((char *)message->payload, "queue") == 0)
            {
                bridgeProtocol = BridgerQueue;
            }
            else if (strcmp((char *)message->payload, "none") == 0)
            {
                bridgeProtocol = DontBridge;
            }
        }
        else if (message->topic == "Wheatstone/bridge")
        {
            if (strcmp((char *)message->payload, "true") == 0)
            {
                enable_bridge = true;
            }
            else if (strcmp((char *)message->payload, "false") == 0)
            {
                enable_bridge = false;
            }
        }
        else if (message->topic == "Wheatstone/status")
        {
            printf("[%s] [%s] %s\n", getCurrentTime().c_str(), get_id_name(id), (char *)message->payload);
        }
        else if (message->topic == "Wheatstone/state")
        {
            printf("[%s] [%s] %s\n", getCurrentTime().c_str(), get_id_name(id), (char *)message->payload);
        }
        else
        {
            printf("[%s] [%s] %s\n", getCurrentTime().c_str(), get_id_name(id), (char *)message->payload);
        }
    }
    

    // printf("[%s][%s] '%s' [mid = %d][qos = %d]\n", get_id_name(id), message->topic, (char *)message->payload, message->mid, message->qos);

    if (bridgeProtocol == Qos && message->qos != 2)
    {
        if (print_router)
            printf("[%S] routing msg from [%s] topic: %s\n", getCurrentTime().c_str(), get_id_name(id), message->topic);

        MqttDevices.addDeviceFromBridge(message->topic, static_cast<deviceSource>(id));
        if (id == HIVE_MQ_ID)
        {
            hivemq_total_messages++;
            mosquitto_publish(mqttLocal, NULL, message->topic, message->payloadlen, message->payload, 2, false);
        }
        else if (id == LOCAL_ID)
        {
            localmq_total_messages++;
            mosquitto_publish(mqttHiveMq, NULL, message->topic, message->payloadlen, message->payload, 2, false);
        }

        for (TcpClient clients : server.ClientsList)
        {
            /// Bridge to tcp, message format defined by Sherlock.
            /// TODO: Change message format.
            ///     : Why the fuck did I setup to send in a format and recieve in another.
            //      : Fuck me.
            if (clients.hasFlag(ClientFlags::RECIEVE_FROM_MQTT))
            {
                std::string tcp_message = "";
                tcp_message += message->topic;
                tcp_message += ",";
                tcp_message += (char *)message->payload;
                server.sendToClient(clients, tcp_message);
            }
        }
    }
    else if (bridgeProtocol == BridgerQueue)
    {
        if (BridgerQ.process(id, message->topic, (char *)message->payload))
        {
            if (id == HIVE_MQ_ID)
            {
                mosquitto_publish(mqttLocal, NULL, message->topic, message->payloadlen, message->payload, 2, false);
            }
            else if (id == LOCAL_ID)
            {
                mosquitto_publish(mqttHiveMq, NULL, message->topic, message->payloadlen, message->payload, 2, false);
            }
        }
    }
    else
    {
        logger.run(message->topic, (char *)message->payload);
        debugger.run(message->topic, (char *)message->payload, get_id_name(id));
    }
}

std::string getMosquittoError(int rc)
{
    if (rc == MOSQ_ERR_SUCCESS)
    {
        return "MOSQ_ERR_SUCCESS";
    }
    else if (rc == MOSQ_ERR_INVAL)
    {
        return "MOSQ_ERR_INVAL";
    }
    else if (rc == MOSQ_ERR_NOMEM)
    {
        return "MOSQ_ERR_NOMEM";
    }
    else if (rc == MOSQ_ERR_NO_CONN)
    {
        return "MOSQ_ERR_NO_CONN";
    }
    else if (rc == MOSQ_ERR_CONN_LOST)
    {
        return "MOSQ_ERR_CONN_LOST";
    }
    else if (rc == MOSQ_ERR_PROTOCOL)
    {
        return "MOSQ_ERR_PROTOCOL";
    }
    else if (rc == MOSQ_ERR_ERRNO)
    {
        return "MOSQ_ERR_ERRNO";
    }
    else
    {
        return "Unknown error";
    }
}

bool start_local_mqtt()
{
    int rc = 0;
    mqttLocal = mosquitto_new(PROJECT_NAME, true, (void *)&LOCAL_ID);
    if (!mqttLocal)
    {
        printf("Error: Out of memory.\n");
        return false;
    }
    printf("Starting local mqtt\n");
    mosquitto_will_set(mqttLocal, "Wheatstone/state", 7, "offline", 2, true);
    mosquitto_connect_callback_set(mqttLocal, connect_callback);
    mosquitto_message_callback_set(mqttLocal, message_callback);
    mosquitto_username_pw_set(mqttLocal, MQTT_USER, MQTT_PASSWD);
    rc = mosquitto_connect(mqttLocal, "127.0.0.1", 1883, 120);
    printf("conn result: %d\n", rc);
    return true;
}

bool start_hivemq_mqtt()
{
    int rc = 0;

    printf("Starting hivemq mqtt\n");
    mqttHiveMq = mosquitto_new(PROJECT_NAME, true, (void *)&HIVE_MQ_ID);
    if (!mqttHiveMq)
    {
        printf("Error: Out of memory.\n");
        return false;
    }

    mosquitto_tls_set(mqttHiveMq, "D:/Projects/C++/App1/isrgrootx1.pem", NULL, NULL, NULL, NULL);
    mosquitto_will_set(mqttHiveMq, "Wheatstone/state", 7, "offline", 2, true);
    mosquitto_connect_callback_set(mqttHiveMq, connect_callback);
    mosquitto_message_callback_set(mqttHiveMq, message_callback);
    mosquitto_username_pw_set(mqttHiveMq, MQTT_USER, MQTT_PASSWD);
    rc = mosquitto_connect(mqttHiveMq, MQTT_URL, MQTT_PORT, 120);
    printf("conn result: %d\n", rc);
    return true;
}

void StartMqttBridger()
{
    mosquitto_lib_init();
    start_hivemq_mqtt();
    start_local_mqtt();
}

void LoopMqttBridger()
{
    static int8_t old_mqtt_status = 0;
    int hiveMqReturnCode = mosquitto_loop(mqttHiveMq, 1000, 1);
    if (hiveMqReturnCode)
    {
        printf("[%s] Hive MQ -> return code: %d - %s \n", getCurrentTime().c_str(), hiveMqReturnCode, getMosquittoError(hiveMqReturnCode).c_str());
        printf("Hive MQ -> connection error!\n");
        mosquitto_reconnect(mqttHiveMq);
        set_mqtt_status_flag(HIVEMQ_CONNECTED, false);
    }
    int localMqReturnCode = mosquitto_loop(mqttLocal, 100, 1);
    if (localMqReturnCode)
    {
        printf("[%s] LocalMQtt -> return code: %d - %s \n", getCurrentTime().c_str(), localMqReturnCode, getMosquittoError(localMqReturnCode).c_str());
        printf("LocalMQtt -> connection error!\n");
        mosquitto_reconnect(mqttLocal);
        set_mqtt_status_flag(LOCAL_CONNECTED, false);
    }
    if (old_mqtt_status != mqtt_status_flags)
    {
        old_mqtt_status = mqtt_status_flags;
        std::string status = std::to_string(mqtt_status_flags);
        mosquitto_publish(mqttHiveMq, NULL, "Wheatstone/status", status.size(), status.c_str(), 2, true);
        mosquitto_publish(mqttLocal, NULL, "Wheatstone/status", status.size(), status.c_str(), 2, true);
        printf("[%s] Mqtt Status: %d\n", getCurrentTime().c_str(), mqtt_status_flags);
    }
    if (std::difftime(std::time(nullptr), Last_state_update) > 300)
    {
        Last_state_update = std::time(nullptr);
        publish_state();
    }
   
}

void FinishMqttBridger()
{
    mosquitto_destroy(mqttHiveMq);
    mosquitto_destroy(mqttLocal);
    mosquitto_lib_cleanup();
}