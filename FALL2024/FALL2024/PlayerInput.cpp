#include "PlayerInput.h"
#include "InputManager.h"

PlayerInput::PlayerInput(int playerId, InputDevice device, GameWindow& wind)
    : playerId(playerId), device(device), window(wind), lastMouseX(0.0), lastMouseY(0.0), deltaX(0.0), deltaY(0.0), firstMouseMove(true) 
{
    glfwSetWindowUserPointer(window.getWindow(), this);

    if (playerId == 0) 
    {
       /* keys.insert({GLFW_KEY_A, false});
        keys.insert({ GLFW_KEY_D, false });*/
        InputManager::AddKey(GLFW_KEY_A);
        InputManager::AddKey(GLFW_KEY_D);
        InputManager::AddKey(GLFW_KEY_SPACE);
        moveLeft = GLFW_KEY_A;
        moveRight = GLFW_KEY_D;
        cMK = GLFW_KEY_SPACE;
    }
    else if (playerId == 1)
    {
        /*keys.insert({GLFW_KEY_LEFT, false});
        keys.insert({ GLFW_KEY_RIGHT, false });*/
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

bool PlayerInput::IsKeyPressed(int key) 
{
    PlayerInput* input = reinterpret_cast<PlayerInput*>(glfwGetWindowUserPointer(window.getWindow()));

    if (!input->keys.contains(key)) 
    {
        return false;
    }

    return input->keys.at(key);
}

bool PlayerInput::IsMouseButtonPressed(int button) const {
    return false;//mouseButtons.at(button);
}

void PlayerInput::GetMousePosition(double& xpos, double& ypos) const {
    glfwGetCursorPos(glfwGetCurrentContext(), &xpos, &ypos);
}

void PlayerInput::GetMouseDelta(double& xoffset, double& yoffset) const {
    xoffset = deltaX;
    yoffset = deltaY;
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