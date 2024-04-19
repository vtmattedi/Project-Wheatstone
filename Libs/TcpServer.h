#undef UNICODE
#pragma once
#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <list>

// Need to link with Ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT (char *)"100"

enum ClientFlags
{
    None = 0,
    SEND_TO_MQTT = 1,
    RECIEVE_FROM_MQTT = 2,
    PRINT_FROM_MQTT = 4
};

/// @brief Client ID struct for compatibility with NightMareNetwork.
struct ClientID
{
    std::string id;
    std::string name;
    std::string info;
    ClientID(std::string message)
    {
        int id_index = message.find("ID::");
        int name_index = message.find("name::");
        int info_index = message.find("info::");
        // -1 to account for the ; at the end of the message.
        if (id_index != std::string::npos)
        {
            id = message.substr(id_index + 4, name_index - id_index - 4 - 1);
        }
        if (name_index != std::string::npos)
        {
            name = message.substr(name_index + 6, info_index - name_index - 6 - 1);
        }
        if (info_index != std::string::npos)
        {

            info = message.substr(info_index + 6, message.size() - info_index - 6 - 1);
        }
    }
};

struct TcpClient
{
private:
    static inline int _nextId = 0;

public:
    SOCKET socket = INVALID_SOCKET;
    int ID;
    SOCKADDR_IN client_info;
    int addrsize = sizeof(client_info);
    std::string ip;
    ClientID client_id = ClientID("ID::0;name::none;info::none;");
    /// @brief for nightmare tcp, 0 = allAvailable, 1 = sizeColon.
    int tmode = 0;
    bool modeSet = false;
    bool debug = false;
    int flags = 0;


    std::string getName()
    {
        if (client_id.name != "none")
        {
            return client_id.name;
        }
        else
        {
            return ip;
        }
    }
    void setFlag(ClientFlags flag, bool value = true)
    {
        if (value)
        {
            flags |= flag;
        }
        else
        {
            flags &= ~flag;
        }
    }

    bool hasFlag(ClientFlags flag)
    {
        return (flags & flag) == flag;
    }
    bool operator==(const TcpClient &other) const
    {
        return socket == other.socket;
    }
    void genInfo()
    {
        getpeername(socket, (SOCKADDR *)&client_info, &addrsize);
        ip = inet_ntoa(client_info.sin_addr);
    }
    TcpClient()
    {
        this->ID = _nextId;
        _nextId++;
    }
    TcpClient(SOCKET socket, SOCKADDR_IN client_info)
    {
        this->socket = socket;
        this->client_info = client_info;
        this->ip = inet_ntoa(client_info.sin_addr);
        this->ID = _nextId;
        _nextId++;
    }
};

class TcpServer
{
public:
    bool (*handleMessage)(TcpClient, std::string) = NULL;
    WSADATA wsaData;
    int iResult;
    char defBuf[DEFAULT_BUFLEN] = {0};
    int bufsize = DEFAULT_BUFLEN;
    bool defaultDebug = false;

    SOCKET ListenSocket = INVALID_SOCKET;

    std::list<TcpClient> ClientsList;

    struct addrinfo *result = NULL;
    struct addrinfo hints;
    u_long imode = 1;

    int iSendResult;

    int __cdecl Start(char *port = DEFAULT_PORT)
    {
        // Initialize Winsock
        iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (iResult != 0)
        {
            printf("WSAStartup failed with error: %d\n", iResult);
            return 1;
        }

        ZeroMemory(&hints, sizeof(hints));
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;
        hints.ai_flags = AI_PASSIVE;

        // Resolve the server address and port
        iResult = getaddrinfo(NULL, port, &hints, &result);
        if (iResult != 0)
        {
            printf("getaddrinfo failed with error: %d\n", iResult);
            WSACleanup();
            return 1;
        }

        // Create a SOCKET for the server to listen for client connections.
        ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
        if (ListenSocket == INVALID_SOCKET)
        {
            printf("socket failed with error: %ld\n", WSAGetLastError());
            freeaddrinfo(result);
            WSACleanup();
            return 1;
        }

        // Setup the TCP listening socket
        iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
        if (iResult == SOCKET_ERROR)
        {
            printf("bind failed with error: %d\n", WSAGetLastError());
            freeaddrinfo(result);
            closesocket(ListenSocket);
            WSACleanup();
            return 1;
        }

        freeaddrinfo(result);

        //-------------------------
        // Set the socket I/O mode: In this case FIONBIO
        // enables or disables the blocking mode for the
        // socket based on the numerical value of iMode.
        // If iMode = 0, blocking is enabled;
        // If iMode != 0, non-blocking mode is enabled.
        iResult = ioctlsocket(ListenSocket, FIONBIO, (unsigned long *)&imode);
        if (iResult != NO_ERROR)
        {
            printf("ioctlsocket failed with error: %d\n", WSAGetLastError());
            WSACleanup();
            return 1;
        }
        iResult = listen(ListenSocket, SOMAXCONN);
        if (iResult == SOCKET_ERROR)
        {
            printf("listen failed with error: %d\n", WSAGetLastError());
            closesocket(ListenSocket);
            WSACleanup();
            return 1;
        }

        printf("Server started at port: [%s]\n", port);
        return 0;
    }

    int __cdecl Stop()
    {
        ClientsList.clear();
        closesocket(ListenSocket);
        WSACleanup();
        return 0;
    }

    int __cdecl Accept()
    {
        // Accept a client socket

        SOCKET newClientSocket = INVALID_SOCKET;
        SOCKADDR_IN client_info;
        int addrsize = sizeof(client_info);
        TcpClient client;
        client.socket = accept(ListenSocket, NULL, NULL);
        if (client.socket == INVALID_SOCKET)
        {
            int error = WSAGetLastError();
            if (error == WSAEWOULDBLOCK)
            {
                return 0;
            }
            printf("accept failed with error: %d\n", error);
            return 1;
        }
        else
        {
            // TcpClient client(newClientSocket, client_info);
            client.genInfo();
            printf("Client connected ip: %s.\n", client.ip.c_str());
            client.debug = defaultDebug;
            sendToClient(client, "REQ_ID");
            ClientsList.push_back(client);
            return 0;
        }
    }

    void killClient(int index)
    {
        int currIndex = 0;
        for (std::list<TcpClient>::iterator it = ClientsList.begin(); it != ClientsList.end(); it++)
        {
            if (currIndex == index)
            {

                iResult = shutdown(it->socket, SD_SEND);
                if (iResult == SOCKET_ERROR)
                {
                    printf("shutdown failed with error: %d\n", WSAGetLastError());
                }
                closesocket(it->socket);
                it = ClientsList.erase(it);
                printf("int Client %d disconnected\n", currIndex);
            }
            currIndex++;
        }
    }

    void killClient(TcpClient client)
    {
        iResult = shutdown(client.socket, SD_SEND);
        if (iResult == SOCKET_ERROR)
        {
            printf("shutdown failed with error: %d\n", WSAGetLastError());
        }
        printf("[sk] Client '%s' disconnected\n", inet_ntoa(client.client_info.sin_addr));
        closesocket(client.socket);
        ClientsList.remove(client);
    }

    bool preHandler(TcpClient *client, std::string message)
    {
        if (message == "TMODE=1" || message == "7:TMODE=1")
        {
            client->tmode = 1;
            printf("[Pre Handler] client '%s' transmission mode set to : 1\n", client->ip.c_str());
            return true;
        }
        else if (message == "TMODE=0" || message == "7:TMODE=0")
        {
            client->tmode = 0;
            printf("[Pre Handler] client '%s' transmission mode set to : 0\n", client->ip.c_str());

            return true;
        }

        if (message == "clients")
        {
            printClients();
            return true;
        }
        if (message == "***keepalive***" || message == "15:***keepalive***")
            return true;

        if (message.find("ID::") != std::string::npos)
        {
            client->client_id = ClientID(message);
            printf("[Pre Handler] client '%s' self indentified:\n -  ID: %s.\n -name: %s.\n -info: %s.\n",
                   client->ip.c_str(), client->client_id.id.c_str(), client->client_id.name.c_str(), client->client_id.info.c_str());
            return true;
        }
        if (message == "REQ_UPDATES")
        {
            client->setFlag(ClientFlags::RECIEVE_FROM_MQTT);
            client->setFlag(ClientFlags::SEND_TO_MQTT);
            printf("[Pre Handler] client '%s' set to recieve and send to mqtt\n", client->ip.c_str());
            return true;
        }

        return false;
    }

    void sendToClient(TcpClient client, std::string message)
    {
        if (client.tmode == 1)
        {
            message = std::to_string(message.size()) + ":" + message;
        }
        if (client.debug)
        {
            printf("Sending: '%s' mode:%d\n", message.c_str(), client.tmode);
        }

        iSendResult = send(client.socket, message.c_str(), message.size(), 0);
        if (iSendResult == SOCKET_ERROR)
        {
            printf("send failed with error: %d.\n", WSAGetLastError());
            killClient(client);
            return;
        }
        // printf("Bytes sent: %d\n", iSendResult);
    }

    int __cdecl loop()
    {
        Accept();
        // Receive until the peer shuts down the connection
        for (auto &client_it : ClientsList)
        {
            std::string message = "";
            /// lets change strats here, will use MSG_PEEK to check the length to be read.
            // if (client.tmode == 1)
            // {
            //     if (client_it.debug)
            //         printf("tmode 1\n");
            //     std::string recvbuffer = "";
            //     char recvchar[1];
            //     iResult = recv(client.socket, recvchar, 1, 0);
            //     while (iResult > 0 && recvchar[0] != ':')
            //     {
            //         recvbuffer += recvchar[0];
            //         iResult = recv(client.socket, recvchar, 1, 0);
            //     }

            //     if (iResult > 0)
            //     {
            //         int size = std::stoi(recvbuffer);
            //         if (size > 0)
            //         {
            //             bufsize = size;
            //             recbuf = new char[bufsize];
            //             iResult = recv(client.socket, recbuf, bufsize, 0);
            //         }
            //     }
            // }
            // else
            // {
            //     if (client_it.debug)
            //         printf("tmode 0\n");
            //     iResult = recv(client.socket, recbuf, bufsize, 0);
            // }

            int colonPos = 0;
            int size = 0;
            bool resolved = false;
            // Check if the trasmission mode is 1 or it is the first message.
            // PEEK the socket stream, to try and parse the size of the message.
            // Than read the size parsed from the buffer.
            if (!client_it.modeSet || client_it.tmode == 1)
            {
                int sizeFindBuf = 10;
                char findBuf[sizeFindBuf];
                iResult = recv(client_it.socket, findBuf, sizeFindBuf, MSG_PEEK);
                if (iResult > 0)
                {
                    // Try to find the colon in pattern size:msg up to 10 chars, so: maxsize is 999999999:{msg that long}
                    auto s = std::string(findBuf);
                    colonPos = s.find(":");
                    if (colonPos != std::string::npos)
                    {
                        if (client_it.debug)
                            printf("*colonPos: %d *s = %s\n ", colonPos, s.c_str());
                        try
                        {
                            size = std::stoi(s.substr(0, colonPos));
                        }
                        catch (const std::exception &e)
                        {
                            size = -1;
                            std::cerr << e.what() << '\n';
                        }

                        // Add the length of the colon and the size to the size
                        if (size > 0)
                            size += colonPos + 1;

                        if (client_it.debug)
                            printf("*size: %d, colonpos: %d\n ", size, colonPos);
                    }
                    else
                        printf("*size not found : %d\n ", colonPos);
                    if (client_it.debug)
                        printf("*Bytes peeked: %d size: %d -> %s\n ", iResult, size, s.c_str());
                    // printf("size: %d\n", size);
                    if (size > 0)
                    {
                        int current_size = __min(size, bufsize);
                        iResult = recv(client_it.socket, defBuf, current_size, 0);
                        //  printf("iResult: %d : c = %d\n", iResult, current_size);
                        if (iResult > 0)
                        {

                            bool sizeBiggerThanBuffer = size > bufsize;
                            message = std::string(defBuf, colonPos + 1, (__min(size, bufsize)) - (colonPos + 1));
                            // Need further testing when size is bigger than buffer. or when there is a size mismatch.
                            if (sizeBiggerThanBuffer)
                            {
                                // Handle incomplete message later
                                if (client_it.debug)
                                    printf("*Message not fully received\n");
                                int remaining = size - iResult;

                                // while data is available try to get the rest of the message
                                while (remaining > 0)
                                {
                                    iResult = recv(client_it.socket, defBuf, remaining > bufsize ? bufsize : remaining, 0);
                                    if (iResult > 0)
                                    {
                                        message += std::string(defBuf, iResult);
                                        remaining -= iResult;
                                    }
                                    else
                                    {
                                        printf("**error finishing to recieved message data ires = %d WSA = %d**\n", iResult, WSAGetLastError());
                                        remaining = -1;
                                    }
                                }
                            }
                            if (client_it.debug)
                                printf("*Bytes received: [%d:%d] -> %s\n", iResult, size - colonPos - 1, message.c_str());
                        }
                        resolved = true;
                    }
                    else
                    {
                        printf("**no size found, defaulting to allAvailable**\n");
                    }
                    client_it.modeSet = true;
                }
            }

            // If the size was not found, or the was an error parsing the size, try to get the message as trasmisson mode allAvailable.
            if (!resolved)
            {
                iResult = recv(client_it.socket, defBuf, bufsize, 0);
                if (iResult > 0)
                {
                    message = std::string(defBuf, iResult);
                    if (client_it.debug)
                        printf("Bytes received: [%d] -> %s\n", iResult, message.c_str());
                }
            }

            // Get the error if there was one.
            int error = WSAGetLastError();
            // if the error is WSAEWOULDBLOCK, the socket is waiting for a message, so we can skip the rest of the loop.
            if (error == WSAEWOULDBLOCK)
            {
                return 0;
            }

            // Message recieved.
            if (iResult > 0)
            {
                // printf("Bytes received: %d\n", iResult);
                bool handled = preHandler(&client_it, message);
                if (handled)
                    sendToClient(client_it, "***ack***");

                if (handleMessage != NULL && !handled)
                {
                    handled = handleMessage(client_it, message);
                }
                if (!handled)
                {
                    sendToClient(client_it, "***ack***");
                }
            }
            // Connection gracefully closed by client.
            else if (iResult == 0)
            {
                printf("Connection closing...\n");
                killClient(client_it);
                return 1;
            }
            // Error receiving message.
            else
            {
                printf("recv failed with error: %d\n", error);
                killClient(client_it);
                return 1;
            }
        }
        return 0;
    }

    void printClients()
    {
        printf("Clients:\n");
        for (TcpClient c : ClientsList)
        {
            printf("client ip = '%s' id = %d tmode = %d\n", c.ip.c_str(), c.ID, c.tmode);
        }
    }
};
