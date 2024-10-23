#include "InputManager.h"

// Static member initialization
GLFWwindow* InputManager::window = nullptr;
std::unordered_map<int, InputManager::KeyState> InputManager::keys;
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
}

void InputManager::Update() {
    // Poll for any GLFW events, such as keyboard and mouse inputs
    for (auto& [key, state] : keys) {
        state.previousState = state.currentState;
    }

    glfwPollEvents();
}

void InputManager::AddKey(int key)
{
    keys.insert({ key, KeyState() });
}

bool InputManager::IsKeyPressed(int key) {
    // Check if key is being held down
    return keys[key].currentState;
}

bool InputManager::IsKeyJustPressed(int key) {
    // Key was pressed this frame but wasn't in the previous frame
    return keys[key].currentState && !keys[key].previousState;
}

bool InputManager::IsKeyJustReleased(int key) {
    // Key was released this frame but was pressed in the previous frame
    return !keys[key].currentState && keys[key].previousState;
}

bool InputManager::IsMouseButtonPressed(int button) {
    // Return the state of the specified mouse button
    return mouseButtons[button];
}

void InputManager::GetMousePosition(double& xpos, double& ypos) {
    // Get the current mouse position
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

    if (action == GLFW_PRESS) {
        keys[key].currentState = true;
    }
    else if (action == GLFW_RELEASE) {
        keys[key].currentState = false;
    }
}

void InputManager::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (action == GLFW_PRESS) {
        mouseButtons[button] = true;
    }
    else if (action == GLFW_RELEASE) {
        mouseButtons[button] = false;
    }
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