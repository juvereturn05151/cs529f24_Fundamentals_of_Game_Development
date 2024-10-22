#ifndef FRAMECONTROLLER_H
#define FRAMECONTROLLER_H

#include <chrono>

class FrameController {
public:
    // Static method to get the singleton instance
    static FrameController& getInstance();

    // Public method to update the delta time
    void update();

    // Getters for deltaTime and FPS
    float getDeltaTime() const;
    float getFPS() const;
    void setTimeScale(float scale);
    float getTimeScale() const;

private:
    // Private constructor to prevent instantiation
    FrameController();
    ~FrameController() {}

    // Deleted copy constructor and assignment operator for Singleton
    FrameController(const FrameController&) = delete;
    FrameController& operator=(const FrameController&) = delete;

    // Time management variables
    std::chrono::high_resolution_clock::time_point lastFrameTime;
    float deltaTime;
    float fps;
    float currentTime;
    float lastTime;
    float timeScale;
};

#endif // FRAMECONTROLLER_H