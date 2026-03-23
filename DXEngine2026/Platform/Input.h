#pragma once
#include <array>
#include <cstdint>

class Input
{
public:
    static void Initialize();
    static void Update();

    static void SetKeyDown(uint8_t key);
    static void SetKeyUp(uint8_t key);

    static bool IsKeyDown(uint8_t key);
    static bool IsKeyHeld(uint8_t key);
    static bool IsKeyUp(uint8_t key);

private:
    static std::array<bool, 256> s_CurrentKeys;
    static std::array<bool, 256> s_PreviousKeys;
};