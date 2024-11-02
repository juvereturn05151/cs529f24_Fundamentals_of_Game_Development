#pragma once
#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

class GameManager
{
protected:
    // Protected constructor to allow inheritance but prevent instantiation
    GameManager() {}
    virtual ~GameManager() {}

    // Deleted copy constructor and assignment operator for Singleton
    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;

public:
    // Static method to get the singleton instance
    static GameManager& getInstance();

    // Pure virtual methods to make the class abstract
    virtual void initialize() = 0;
    virtual void update() = 0;
    virtual void reset() = 0;
};

#endif // GAMEMANAGER_H