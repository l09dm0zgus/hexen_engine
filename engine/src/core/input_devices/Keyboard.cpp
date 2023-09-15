//
// Created by cx9ps3 on 14.09.2023.
//

#include "Keyboard.hpp"

bool hexen::engine::core::input::Keyboard::processInput(const SDL_Event &event)
{
    SDL_PumpEvents();

    auto isKeyboardEvent = event.type == SDL_EVENT_KEY_UP || event.type == SDL_EVENT_KEY_DOWN;

    if(isKeyboardEvent)
    {
        currentKeyScancode = event.key.keysym.scancode;
    }

    return isKeyboardEvent;
}

hexen::engine::core::input::Keyboard::Keyboard()
{
    keyboardState = SDL_GetKeyboardState(nullptr);
}

bool hexen::engine::core::input::Keyboard::isKeyPressed(hexen::engine::core::input::Keyboard::Key key)
{
    if(keyboardState != nullptr)
    {
        return keyboardState[static_cast<u32>(key)];
    }
    return false;
}
