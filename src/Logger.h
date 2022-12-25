#ifndef LOGGER_H
#define LOGGER_H

#include <string>

class Logger {
    
    struct LogEntry {
        std::string color;
        std::string type;
        std::string message;
    };

    private:
        inline static const std::string GREY = "\033[1;90m";
        inline static const std::string RED = "\033[1;32m";
        inline static const std::string END = "\033[0m";


        inline static const std::string LOG = "LOG";
        inline static const std::string ERR = "ERR";

        static std::string TimeToString();
        static void Print(LogEntry logEntry);
    public:
        //TODO: remove static modifier
        static void Log(const std::string& message);
        static void Err(const std::string& message);
};

#endif