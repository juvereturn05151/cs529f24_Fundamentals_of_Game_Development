#include "PlayerInput.h"

PlayerInput::PlayerInput(int playerId, InputDevice device, GameWindow& wind)
    : playerId(playerId), device(device), window(wind), lastMouseX(0.0), lastMouseY(0.0), deltaX(0.0), deltaY(0.0), firstMouseMove(true) 
{
    glfwSetWindowUserPointer(window.getWindow(), this);

    keys.insert({GLFW_KEY_A, false});

    keys.insert({ GLFW_KEY_D, false });
    // Set GLFW callbacks for input
    glfwSetKeyCallback(window.getWindow(), KeyCallback);
    glfwSetMouseButtonCallback(window.getWindow(), MouseButtonCallback);


}

void PlayerInput::Update() {
    if (device == KeyboardMouse) {
        UpdateKeyboardMouse();
    }
    else if (device == Gamepad) {
        UpdateGamepad();
    }
}

void PlayerInput::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // Update key state
    PlayerInput* input = reinterpret_cast<PlayerInput*>(glfwGetWindowUserPointer(window));

    if (action == GLFW_PRESS) {

        input->keys[key] = true;
    }
    else if (action == GLFW_RELEASE) {
        input->keys[key] = false;
    }
}

// Static mouse button callback function for GLFW
void PlayerInput::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) 
{
    
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