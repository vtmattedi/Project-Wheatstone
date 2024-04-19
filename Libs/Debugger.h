#ifndef DEBUGGER_H
#define DEBUGGER_H

#include <iostream>
#include <filesystem>
#include <windows.h>
#include <string>
#include <iostream>
#include <list>

class Debugger {
public:
    std::list<std::string> topics;

    void run (const std::string topic,const std::string message, const std::string name) {
        for (std::string _topic : topics) {
            if (_topic == topic) {
                   printf("[%s][%s] '%s'\n", name.c_str(), topic.c_str(), message.c_str());
            }
        }
    }

    std::string currentTopics() {
        
        std::string _topics = "current topics: ";	
        for (std::string topic : topics) {
            _topics += topic + "\n";
        }
        
        return _topics;
    }

};

#endif // DEBUGGER_H