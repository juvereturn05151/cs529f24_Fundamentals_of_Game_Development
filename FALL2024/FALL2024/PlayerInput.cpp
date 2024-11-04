#include "PlayerInput.h"
#include "InputManager.h"

PlayerInput::PlayerInput(int playerId, InputDevice device, GameWindow& wind)
    : playerId(playerId), device(device), window(wind), lastMouseX(0.0), lastMouseY(0.0), deltaX(0.0), deltaY(0.0), firstMouseMove(true) 
{
    glfwSetWindowUserPointer(window.getWindow(), this);

    if (playerId == 0) 
    {
        InputManager::AddKey(GLFW_KEY_A);
        InputManager::AddKey(GLFW_KEY_D);
        InputManager::AddKey(GLFW_KEY_SPACE);
        moveLeft = GLFW_KEY_A;
        moveRight = GLFW_KEY_D;
        cMK = GLFW_KEY_SPACE;
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

        int axesCount;
        const float* axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1 + playerId, &axesCount);
        gamepadLeftX = axes[0];
        gamepadLeftY = axes[1];
        gamepadRightX = axes[2]; // Right stick, depending on the joystick configuration
        gamepadRightY = axes[3];
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