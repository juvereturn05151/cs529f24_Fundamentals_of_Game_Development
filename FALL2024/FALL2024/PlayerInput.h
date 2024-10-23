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

    // Query input actions for the player
    bool IsKeyPressed(int key);
    bool IsMouseButtonPressed(int button) const;

    void GetMousePosition(double& xpos, double& ypos) const;
    void GetMouseDelta(double& xoffset, double& yoffset) const;

    bool IsGamepadButtonPressed(int button) const;
    void GetGamepadAxes(float& leftX, float& leftY, float& rightX, float& rightY) const;

    int GetMoveLeft();
    int GetMoveRight();
    int GetcMK();

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

    int moveLeft = -1;
    int moveRight = -1;
    int cMK = -1;
};

#endif