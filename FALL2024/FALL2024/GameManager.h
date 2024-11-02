#pragma once
#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

class GameManager
{
private:
    // Private constructor to prevent instantiation
    GameManager() {}
    ~GameManager() {}

    // Deleted copy constructor and assignment operator for Singleton
    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;
public:
    // Static method to get the singleton instance
    static GameManager& getInstance();

    virtual void initialize();

    virtual void update();

    virtual void reset();
};

#endif // GAMEMANAGER_H