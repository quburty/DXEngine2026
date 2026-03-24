#pragma once

class Time
{
public:
    static void Init();
    static void Update();

    static float GetDeltaTime();
    static float GetTotalTime();

private:
    static double s_DeltaTime;
    static double s_TotalTime;
    static long long s_Frequency;
    static long long s_LastCounter;
};