#include "Input.h"

std::array<bool, 256> Input::s_CurrentKeys = {};
std::array<bool, 256> Input::s_PreviousKeys = {};

void Input::Initialize()
{
    s_CurrentKeys.fill(false);
    s_PreviousKeys.fill(false);
}

void Input::Update()
{
    s_PreviousKeys = s_CurrentKeys;
}

void Input::SetKeyDown(uint8_t key)
{
    s_CurrentKeys[key] = true;
}

void Input::SetKeyUp(uint8_t key)
{
    s_CurrentKeys[key] = false;
}

bool Input::IsKeyDown(uint8_t key)
{
    return s_CurrentKeys[key] && !s_PreviousKeys[key];
}

bool Input::IsKeyHeld(uint8_t key)
{
    return s_CurrentKeys[key];
}

bool Input::IsKeyUp(uint8_t key)
{
    return !s_CurrentKeys[key] && s_PreviousKeys[key];
}