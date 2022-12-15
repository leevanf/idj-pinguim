#include "InputManager.h"
#include <iostream>
#include "SDL.h"

InputManager::InputManager() {
    updateCounter = 0;
    quitRequested = false;
    mouseX = 0;
    mouseY = 0;
}

InputManager::~InputManager() {

}

void InputManager::Update() {
    SDL_Event event;
    quitRequested = false;
    SDL_GetMouseState(&mouseX, &mouseY);
    updateCounter++;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN:
                if (event.key.repeat != 1) {
                    keyState[event.key.keysym.sym] = true;
                    keyUpdate[event.key.keysym.sym] = updateCounter;
                }
                break;
            case SDL_KEYUP:
                keyState[event.key.keysym.sym] = false;
                keyUpdate[event.key.keysym.sym] = updateCounter;
                break;
            case SDL_MOUSEBUTTONDOWN:
                mouseState[event.button.button] = true;
                mouseUpdate[event.button.button] = updateCounter;
                break;
            case SDL_MOUSEBUTTONUP:
                mouseState[event.button.button] = false;
                mouseUpdate[event.button.button] = updateCounter;
                break;
            case SDL_QUIT:
                quitRequested = true;
                break;
            default:
                break;
        }
    }
}

bool InputManager::KeyPress(int key) {
    return (keyState[key] && keyUpdate[key] == updateCounter);
}

bool InputManager::KeyRelease(int key) {
    return (!keyState[key] && keyUpdate[key] == updateCounter);
}

bool InputManager::IsKeyDown(int key) {
    return keyState[key];
}

bool InputManager::MousePress(int button) {
    return (mouseState[button] && mouseUpdate[button] == updateCounter);
}

bool InputManager::MouseRelease(int button) {
    return (!mouseState[button] && mouseUpdate[button] == updateCounter);
}

bool InputManager::IsMouseDown(int button) {
    return mouseState[button];
}