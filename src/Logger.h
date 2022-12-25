#ifndef LOGGER_H
#define LOGGER_H

#include <string>

class Logger {
    //TODO: this will be an interface, once we have imgui a imguiLogger will be created
    
    struct LogEntry {
        std::string color;
        std::string type;
        std::string message;
    };

    private:
        const std::string GREY = "\033[1;90m";
        const std::string RED = "\033[1;31m";
        const std::string END = "\033[0m";


        const std::string LOG = "LOG";
        const std::string ERR = "ERR";

        std::string TimeToString();
        void Print(LogEntry logEntry);
    public:
        void Log(const std::string& message);
        void Err(const std::string& message);
};

#endif