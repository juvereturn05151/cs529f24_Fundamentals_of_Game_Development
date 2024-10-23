#ifndef PLAYER_INPUT_H
#define PLAYER_INPUT_H

#include <unordered_map>
#include "GameWindow.h"

enum InputDevice {
    KeyboardMouse,
    Gamepad
};

class PlayerInput {
public:
    PlayerInput(int playerId, InputDevice device, GameWindow& wind);

    // Update player-specific input
    void Update();

    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

    // Query input actions for the player
    bool IsKeyPressed(int key);
    bool IsMouseButtonPressed(int button) const;

    void GetMousePosition(double& xpos, double& ypos) const;
    void GetMouseDelta(double& xoffset, double& yoffset) const;

    bool IsGamepadButtonPressed(int button) const;
    void GetGamepadAxes(float& leftX, float& leftY, float& rightX, float& rightY) const;

private:
    GameWindow& window;

    int playerId;  // Player's ID
    InputDevice device;  // The input device used by this player

    // Keyboard/Mouse states
    std::unordered_map<int, bool> keys;
    //std::unordered_map<int, bool> mouseButtons;
    double lastMouseX, lastMouseY;
    double deltaX, deltaY;
    bool firstMouseMove;

    // Gamepad states
    //std::unordered_map<int, bool> gamepadButtons;
    float gamepadLeftX, gamepadLeftY;
    float gamepadRightX, gamepadRightY;

    // Internal functions to handle input updates
    void UpdateKeyboardMouse();
    void UpdateGamepad();
};

#endif