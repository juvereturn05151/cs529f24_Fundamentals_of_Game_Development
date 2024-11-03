#include "SoundManager.h"

SoundManager::SoundManager() 
{
    soundEngine = createIrrKlangDevice();
    if (!soundEngine) 
    {
        throw std::runtime_error("Could not initialize IrrKlang sound engine");
    }
}

// Private destructor
SoundManager::~SoundManager() 
{
    if (soundEngine) 
    {
        soundEngine->drop();
    }
}

// Public methods for sound control
void SoundManager::playSound(const std::string& filePath, bool loop = false) 
{
    if (soundEngine) 
    {
        soundEngine->play2D(filePath.c_str(), loop);
    }
}

void SoundManager::stopAllSounds() 
{
    if (soundEngine) 
    {
        soundEngine->stopAllSounds();
    }
}

void SoundManager::setVolume(float volume) 
{
    if (soundEngine) 
    {
        soundEngine->setSoundVolume(volume);
    }
}