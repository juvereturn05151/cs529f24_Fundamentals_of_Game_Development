#include "PlayerInput.h"
#include "InputManager.h"

PlayerInput::PlayerInput(int playerId, InputDevice device, GameWindow& wind)
    : playerId(playerId), device(device), window(wind)
{
    glfwSetWindowUserPointer(window.getWindow(), this);

    if (playerId == 0) 
    {
        InputManager::AddKey(GLFW_KEY_A);
        InputManager::AddKey(GLFW_KEY_D);
        InputManager::AddKey(GLFW_KEY_SPACE);
        InputManager::AddButton(GLFW_GAMEPAD_BUTTON_DPAD_DOWN);
        InputManager::AddButton(GLFW_GAMEPAD_BUTTON_DPAD_UP);
        InputManager::AddButton(GLFW_GAMEPAD_BUTTON_A);
        moveLeft = GLFW_KEY_A;
        moveRight = GLFW_KEY_D;
        cMK = GLFW_KEY_SPACE;
        moveLeftController = GLFW_GAMEPAD_BUTTON_DPAD_DOWN;
        moveRightController = GLFW_GAMEPAD_BUTTON_DPAD_UP;
        cMKController = GLFW_GAMEPAD_BUTTON_A;
    }
    else if (playerId == 1)
    {
        InputManager::AddKey(GLFW_KEY_LEFT);
        InputManager::AddKey(GLFW_KEY_RIGHT);
        InputManager::AddKey(GLFW_KEY_RIGHT_SHIFT);
        moveLeft = GLFW_KEY_LEFT;
        moveRight = GLFW_KEY_RIGHT;
        cMK = GLFW_KEY_RIGHT_SHIFT;
    }
    // Set GLFW callbacks for input
}

void PlayerInput::Update() {
    if (device == KeyboardMouse) {
        UpdateKeyboardMouse();
    }
    else if (device == Gamepad) {
        UpdateGamepad();
    }
}

void PlayerInput::UpdateKeyboardMouse() {
    // Poll keyboard and mouse inputs (similar to the previous InputManager design)
    glfwPollEvents();
}

void PlayerInput::UpdateGamepad() {
    // Handle gamepad inputs using GLFW gamepad APIs
    /*if (glfwJoystickPresent(GLFW_JOYSTICK_1 + playerId)) {
        int buttonCount;
        const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1 + playerId, &buttonCount);
        for (int i = 0; i < buttonCount; i++) {
            gamepadButtons[i] = buttons[i] == GLFW_PRESS;
        }
    }*/
}

int PlayerInput::GetMoveLeft()
{
    return moveLeft;
}

int PlayerInput::GetMoveRight()
{
    return moveRight;
}

int PlayerInput::GetcMK()
{
    return cMK;
}

int PlayerInput::GetMoveLeftController()
{
    return moveLeftController;
}

int PlayerInput::GetMoveRightController()
{
    return moveRightController;
}

int PlayerInput::GetcMKController()
{
    return cMKController;
}