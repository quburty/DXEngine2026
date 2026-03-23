#include "Logger.h"
#include <Windows.h>
#include <iostream>

void Logger::Init()
{
    AllocConsole();
    FILE* fp;
    freopen_s(&fp, "CONOUT$", "w", stdout);
    freopen_s(&fp, "CONOUT$", "w", stderr);

    Info("Logger initialized.");
}

void Logger::Shutdown()
{
    Info("Logger shutdown.");
    FreeConsole();
}

void Logger::Info(const std::string& message)
{
    Print("INFO", message);
}

void Logger::Warn(const std::string& message)
{
    Print("WARN", message);
}

void Logger::Error(const std::string& message)
{
    Print("ERROR", message);
}

void Logger::Print(const std::string& level, const std::string& message)
{
    std::string full = "[" + level + "] " + message + "\n";
    std::cout << full;
    OutputDebugStringA(full.c_str());
}