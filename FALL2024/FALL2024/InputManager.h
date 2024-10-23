#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <GLFW/glfw3.h>
#include <iostream>
#include <unordered_map>


class InputManager {
public:
    // Initializes the input manager with the GLFW window context
    static void Initialize(GLFWwindow* window);

    // Updates the input states, should be called every frame
    static void Update();

    static void AddKey(int key);

    // Key press detection
    static bool IsKeyPressed(int key);
    static bool IsKeyJustPressed(int key);   // Check if key was just pressed this frame
    static bool IsKeyJustReleased(int key);

    // Mouse button press detection
    static bool IsMouseButtonPressed(int button);

    // Get current mouse position
    static void GetMousePosition(double& xpos, double& ypos);

    // Get mouse movement delta
    static void GetMouseDelta(double& xoffset, double& yoffset);

    // Callbacks for GLFW input events
    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos);

private:
    static GLFWwindow* window;  // Reference to the window

    struct KeyState 
    {
        bool currentState = false;
        bool previousState = false;
    };
    
    // Track key and mouse button states
    static std::unordered_map<int, KeyState> keys;
    static std::unordered_map<int, bool> mouseButtons;

    // Mouse position and movement tracking
    static double lastX, lastY;
    static double deltaX, deltaY;
    static bool firstMouseMovement;  // To detect first mouse position update
};

#endif