#include <fstream>
#include <string>
#include <chrono>
#include <ctime>
#include <list>
#include <filesystem>
#include <windows.h>
#include <string>
#include <iostream>

std::string myDir() {
    TCHAR buffer[MAX_PATH] = { 0 };
    GetModuleFileName( NULL, buffer, MAX_PATH );
    // std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
    // return std::wstring(buffer).substr(0, pos).c_str();
    return std::string(buffer).substr(0, std::string(buffer).find_last_of("\\"));
}

// Get current time in DD/MM/YY HH:mm format
std::string getCurrentTime()
{
    std::time_t now = std::time(nullptr);
    std::tm *timeinfo = std::localtime(&now);
    char buffer[20];
    std::strftime(buffer, sizeof(buffer), "%d/%m/%y %H:%M", timeinfo);
    return std::string(buffer);
}

struct Logger
{
    std::string logs_dir = myDir() + "/logs/";
    std::list<std::string> topics;
    Logger()
    {
        if (!std::filesystem::is_directory(logs_dir))
        {
            printf("creating logs directory\n");
            std::filesystem::create_directory(logs_dir);
        //   // Create logs directory if it doesn't exist
        // std::string command = "mkdir -p " + logs_dir;
        // system(command.c_str());
        }
        
       
    }

    void run(const std::string topic, const std::string &message)
    {
        for (std::string _topic : topics)
        {
            if (_topic == topic)
            {
                std::string topicname = topic;
                topicname.replace(topicname.find("/"), 1, "_");
                std::string filename = logs_dir + topicname + ".txt";
               // printf("\nwriting to '%s'\n",filename.c_str());
                std::ofstream file(filename, std::ios::app);
                if (file.is_open())
                {
                    file << "" << getCurrentTime() << ", " << message << std::endl;
                    file.close();
                }
                else
                {
                    printf("error\n");
                }
            }
        }
    }
    void addTopic(const std::string topic)
    {
        //topics = dasd as
        topics.push_back(topic);
    }
};