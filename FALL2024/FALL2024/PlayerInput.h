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

    int GetMoveLeft();
    int GetMoveRight();
    int GetcMK();
    int GetMoveLeftController();
    int GetMoveRightController();
    int GetcMKController();

private:
    GameWindow& window;

    int playerId;  // Player's ID
    InputDevice device;  // The input device used by this player

    // Internal functions to handle input updates
    void UpdateKeyboardMouse();
    void UpdateGamepad();

    int moveLeft = -1;
    int moveRight = -1;
    int cMK = -1;
    int moveLeftController = -1;
    int moveRightController = -1;
    int cMKController = -1;
};

#endif