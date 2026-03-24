#include "Time.h"
#include <Windows.h>

double Time::s_DeltaTime = 0.0;
double Time::s_TotalTime = 0.0;
long long Time::s_Frequency = 0;
long long Time::s_LastCounter = 0;

void Time::Init()
{
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    s_Frequency = freq.QuadPart;

    LARGE_INTEGER counter;
    QueryPerformanceCounter(&counter);
    s_LastCounter = counter.QuadPart;
}

void Time::Update()
{
    LARGE_INTEGER counter;
    QueryPerformanceCounter(&counter);

    s_DeltaTime = static_cast<double>(counter.QuadPart - s_LastCounter) / static_cast<double>(s_Frequency);
    s_LastCounter = counter.QuadPart;
    s_TotalTime += s_DeltaTime;
}

float Time::GetDeltaTime()
{
    return static_cast<float>(s_DeltaTime);
}

float Time::GetTotalTime()
{
    return static_cast<float>(s_TotalTime);
}