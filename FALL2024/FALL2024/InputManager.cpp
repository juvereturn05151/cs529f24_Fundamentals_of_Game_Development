#include "InputManager.h"

// Static member initialization
GLFWwindow* InputManager::window = nullptr;
std::unordered_map<int, InputManager::KeyState> InputManager::keys;
std::unordered_map<int, InputManager::KeyState> InputManager::gamepadButtons;
std::unordered_map<int, bool> InputManager::mouseButtons;
double InputManager::lastX = 0.0;
double InputManager::lastY = 0.0;
double InputManager::deltaX = 0.0;
double InputManager::deltaY = 0.0;
bool InputManager::firstMouseMovement = true;

void InputManager::Initialize(GLFWwindow* windowContext) {
    window = windowContext;

    // Set GLFW input callbacks
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetMouseButtonCallback(window, MouseButtonCallback);
    glfwSetCursorPosCallback(window, CursorPositionCallback);
    glfwSetJoystickCallback(JoystickCallback);
}

void InputManager::Update() {
    // Iterate over all key states
    for (auto& [key, state] : keys) {
        // Reset the pressed and released states for the new frame
        state.pressed = false;
        state.released = false;

        // Get the current GLFW key state (pressed or released)
        int glfwState = glfwGetKey(window, key);

        // If the key is pressed in GLFW
        if (glfwState == GLFW_PRESS) {
            if (!state.held) {
                state.pressed = true;   // Key was just pressed
            }
            state.held = true;  // Key is being held
        }
        // If the key is released in GLFW
        else if (glfwState == GLFW_RELEASE) {
            if (state.held) {
                state.released = true;  // Key was just released
            }
            state.held = false;  // Key is no longer held
        }
    }

    // Update gamepad buttons
    if (glfwJoystickPresent(GLFW_JOYSTICK_1)) {
        int buttonCount;
        const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);

        for (int i = 0; i < buttonCount; i++) {
            if (buttons[i] == GLFW_PRESS) {
                std::cout << "Button " << i << " is pressed." << std::endl;
            }
        }
        // Iterate over each button and update its state
        for (auto& [button, state] : gamepadButtons) {
            // Reset the pressed and released states for the new frame
            state.pressed = false;
            state.released = false;

            // Check if the button index is within the range of available buttons
            if (button < buttonCount) {
                bool isPressed = (buttons[button] == GLFW_PRESS);

                if (isPressed) {
                    if (!state.held) {
                        state.pressed = true; // Button was just pressed
                    }
                    state.held = true; // Button is being held
                }
                else {
                    if (state.held) {
                        state.released = true; // Button was just released
                    }
                    state.held = false; // Button is no longer held
                }
            }
        }
    }

    // Process other GLFW events
    glfwPollEvents();
}

void InputManager::AddKey(int key) 
{
    keys.insert({ key, KeyState() });
}

void InputManager::AddButton(int button)
{
    gamepadButtons.insert({ button, KeyState() });
}

bool InputManager::IsKeyPressed(int key) {
    return keys[key].held;
}

bool InputManager::IsKeyJustPressed(int key) {
    return keys[key].pressed;
}

bool InputManager::IsKeyJustReleased(int key) {
    return keys[key].released;
}

bool InputManager::IsGamepadButtonPressed(int button)
{
    return gamepadButtons[button].held;
}

bool InputManager::IsGamepadButtonJustPressed(int button)
{
    return gamepadButtons[button].pressed;
}

bool InputManager::IsGamepadButtonJustReleased(int button)
{
    return gamepadButtons[button].released;
}

bool InputManager::IsMouseButtonPressed(int button) {
    return mouseButtons[button];
}

void InputManager::GetMousePosition(double& xpos, double& ypos) {
    glfwGetCursorPos(window, &xpos, &ypos);
}

void InputManager::GetMouseDelta(double& xoffset, double& yoffset) {
    xoffset = deltaX;
    yoffset = deltaY;
}

void InputManager::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (keys.find(key) == keys.end()) {
        keys[key] = KeyState(); // Initialize if not present
    }

    if (action == GLFW_PRESS) 
    {
        keys[key].pressed = true;
        keys[key].held = true;
    }
    else if (action == GLFW_RELEASE)
    {
        keys[key].released = true;
        keys[key].held = false;
    }
}

void InputManager::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    mouseButtons[button] = (action == GLFW_PRESS);
}

void InputManager::CursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouseMovement) {
        lastX = xpos;
        lastY = ypos;
        firstMouseMovement = false;
    }

    deltaX = xpos - lastX;
    deltaY = lastY - ypos;  // Inverted since y-coordinates range from bottom to top
    lastX = xpos;
    lastY = ypos;
}

void InputManager::JoystickCallback(int jid, int event) {
    if (event == GLFW_CONNECTED) {
        std::cout << "Joystick " << jid << " connected\n";
    }
    else if (event == GLFW_DISCONNECTED) {
        std::cout << "Joystick " << jid << " disconnected\n";
    }
}