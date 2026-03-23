#pragma once
#include <string>

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