#include "Logger.h"
#include <iostream>
#include <chrono>

void Logger::Log(const std::string& message) {
    LogEntry logEntry;
    logEntry.color = Logger::GREY;
    logEntry.type = Logger::LOG;
    logEntry.message = message;
    Logger::Print(logEntry);
}

void Logger::Err(const std::string& message) {
    LogEntry logEntry;
    logEntry.color = Logger::RED;
    logEntry.type = Logger::ERR;
    logEntry.message = message;
    Logger::Print(logEntry);
}

void Logger::Print(LogEntry logEntry) {
    std::string output = logEntry.type + " [" + Logger::TimeToString() + "]: " + logEntry.message;
    std::cout << logEntry.color << output << Logger::END << std::endl;
}

std::string Logger::TimeToString() {
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::string buffer(30, '\0');
    std::strftime(&buffer[0], buffer.size(), "%d-%b-%Y %H:%M:%S", std::localtime(&now));
    return buffer;
}