#pragma once
#include <irrKlang.h>
#include <string>
#include <stdexcept>
using namespace irrklang;

class SoundManager
{
private:
	// Pointer to the sound engine
	ISoundEngine* soundEngine; 
	SoundManager();
	~SoundManager();
public:
	// Static method to get the single instance of the SoundManager
	static SoundManager& getInstance() 
	{
		// Guaranteed to be destroyed and instantiated on first use
		static SoundManager instance; 
		return instance;
	}

	// Delete copy constructor and assignment operator to prevent copying
	SoundManager(const SoundManager&) = delete;
	SoundManager& operator=(const SoundManager&) = delete;

	void playSound(const std::string& filePath, bool loop = false);
	void stopAllSounds();
	void setVolume(float volume);
};

