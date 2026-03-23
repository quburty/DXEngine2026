#include "Core/Application.h"
#include "Core/Logger.h"

int main()
{
    Logger::Init();

    {
        Application app;
        if (!app.Initialize())
        {
            Logger::Error("Application failed to initialize.");
            Logger::Shutdown();
            return -1;
        }

        app.Run();
        app.Shutdown();
    }

    Logger::Shutdown();
    return 0;
}