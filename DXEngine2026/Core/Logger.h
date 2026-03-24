#pragma once
#include <string>

#define LOG_INFO(msg) Logger::Info(msg)
#define LOG_WARN(msg) Logger::Warn(msg)
#define LOG_ERROR(msg) Logger::Error(msg)

class Logger
{
public:
    static void Init();
    static void Shutdown();

    static void Info(const std::string& message);
    static void Warn(const std::string& message);
    static void Error(const std::string& message);

private:
    static void Print(const std::string& level, const std::string& message);
};