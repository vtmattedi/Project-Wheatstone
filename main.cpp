#include <iostream>
#include <string.h>
#include <stdio.h>
#include <D:\Projects\C++\App1\Libs\TcpServer.h>
#include <chrono>
#include <thread>
#include <list>
#include <D:\Projects\C++\App1\Libs\MqttBridger.h>
#include <D:\Projects\C++\App1\Libs\misc.h>
#include <bits/stdc++.h>


TcpServer server;

#define DEBUG_CMD FALSE

struct Command_result
{
    std::string response = "";
    bool result = false;
};

// directly from https://en.cppreference.com/w/cpp/string/byte/toupper
std::string str_toupper(std::string s)
{
    std::transform(s.begin(), s.end(), s.begin(),
                   // static_cast<int(*)(int)>(std::toupper)         // wrong
                   // [](int c){ return std::toupper(c); }           // wrong
                   // [](char c){ return std::toupper(c); }          // wrong
                   [](unsigned char c)
                   { return std::toupper(c); } // correct
    );
    return s;
}

Command_result handleInput(std::string input)
{

    std::string command = "";
    std::string args[5] = {"", "", "", "", ""};
    std::string current_str = "";
    int current_arg = 0;
    // Gets the command and the arguments.
    for (size_t i = 0; i < input.size(); i++)
    {
        if (input[i] == ' ')
        {
            if (current_arg == 0)
            {
                command = str_toupper(current_str);
            }
            else
            {
                args[current_arg - 1] = current_str;
            }
            current_str = "";
            current_arg++;
            if (current_arg > 5)
            {
                i = input.size();
            }
        }
        else
        {
            current_str += input[i];
        }
    }
    if (current_arg <= 5)
    {
        if (current_arg == 0)
            command = str_toupper(current_str);
        else
            args[current_arg - 1] = current_str;
    }

    if (DEBUG_CMD)
    {
        printf("Command: %s\n", command.c_str());
        for (size_t i = 0; i < 5; i++)
        {
            printf("  --arg[%d]: %s\n", i, args[i].c_str());
        }
    }

    Command_result result{
        .response = "",
        .result = true};
    if (input == "exit")
    {
        result.response = "exit";
    }
    else if (command == "DIR")
    {

        result.response = "dir:\n";
        result.response += myDir();
        result.response += "\nlogs dir:\n";
        result.response += myDir() + logger.logs_dir;
        result.response += "\n";
    }
    else if (command == "DEVICES")
    {
        result.response = "Devices:\n";
        for (auto &device : MqttDevices.devices)
        {

            result.response += formatString("--Device :'%s' Source: '%s'\n",
                                            device.first.c_str(),
                                            deviceSourceToString(device.second).c_str());
        }
    }

    else if (command == "LOGGER")
    {

        result.response = "Logger topics:\n";
        for (std::string topic : logger.topics)
        {
            result.response += " * '";
            result.response += topic;
            result.response += "'\n";
        }
    }
    else if (command == "INFO")
    {
        result.response = formatString("Msg inbound Hivmq: %d\nMsgs inbound local: %d\n", hivemq_total_messages, localmq_total_messages);
    }
    else if (command == "SHOWROUTE")
    {
        if (args[0] == "true" || args[0] == "1")
        {
            print_router = 1;
        }
        else if (args[0] == "false" || args[0] == "0")
        {
            print_router = 0;
        }

        print_router = !print_router;
        result.response = formatString("Print router is now: [%d]\n", print_router);
    }
    else
    {
        result.response = "Unknown command";
        result.result = false;
    }

    return result;
}

bool handleTCP(TcpClient client, std::string message)
{
    if (client.hasFlag(ClientFlags::SEND_TO_MQTT))
    {
        int size = message.size();
        int payload_index = message.find("payload::");
        int topic_index = message.find("topic::");
        if (payload_index != std::string::npos && topic_index != std::string::npos)
        {
            std::string topic = message.substr(topic_index + 7, payload_index - topic_index - 7);
            std::string msg = message.substr(payload_index + 9, size - payload_index - 9);
            mosquitto_publish(mqttHiveMq, NULL, topic.c_str(), msg.size(), msg.c_str(), 2, false);
            mosquitto_publish(mqttLocal, NULL, topic.c_str(), msg.size(), msg.c_str(), 2, false);
            if (print_router)
                printf("routing msg from [TCP:%s] topic: %s\n", client.getName().c_str(), topic.c_str());
        }
        else
        {
            printf("Invalid message format: '%s'\n", message.c_str());
        }
    }

    Command_result res = handleInput(message);
    server.sendToClient(client, res.response);
    return res.result;
    // printf("[%s]: '%s'\n", inet_ntoa(client.client_info.sin_addr), message.c_str());
}

int main(int, char **)
{
    
    logger.addTopic("Adler/Debug");
    logger.addTopic("Adler/state");
    logger.addTopic("Adler/WAIT");
    std::cout << "Project Wheatstone started!\n";
    bool tcp_server_started = false;
    server.handleMessage = handleTCP;
    // server.defaultDebug = true;
    int res = server.Start("101");
    if (res)
    {
        printf("Error starting server\n");
    }
    else
        tcp_server_started = true;

    StartMqttBridger();
    while (true)
    {
        LoopMqttBridger();
        server.loop();
    }
    FinishMqttBridger();
}
