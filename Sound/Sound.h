#ifndef SOUND_H
#define SOUND_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>

// Handles loading and controlling a single sound (MP3 supported)
class Sound {
public:

    // Constructor
    //
    // RETURNS:
    // Creates an empty sound instance, not yet loaded
    Sound(const std::string& filePath);

    // Constructor
    //
    // RETURNS:
    // Creates an empty sound instance, not yet loaded
    Sound();


    // Destructor
    //
    // RETURNS:
    // Frees the loaded sound and closes SDL_mixer if needed
    ~Sound();

    // Loads a sound file
    //
    // RETURNS:
    // True if loading succeeded, false otherwise
    bool load(const std::string& filePath);

    // Plays the sound from the beginning
    //
    // RETURNS:
    // True if playback started, false otherwise
    bool play();

    // Pauses the currently playing sound
    //
    // RETURNS:
    // True if the sound was paused, false otherwise
    bool pause();

    // Resumes playback if the sound was paused
    //
    // RETURNS:
    // True if resumed, false otherwise
    bool resume();

    // Stops the currently playing sound
    //
    // RETURNS:
    // True if the sound was stopped, false otherwise
    bool stop();

    // Checks if the sound is currently playing
    //
    // RETURNS:
    // True if playing, false otherwise
    bool isPlaying() const;

    // Sets the volume for this sound instance
    //
    // volume: 0 (mute) to 128 (max)
    // RETURNS: void
    void setVolume(int volume);

private:

    // Pointer to the loaded sound chunk
    Mix_Chunk* chunk;

    // Channel number used to play this sound
    int channel;

    // Whether SDL_mixer has been initialized globally
    static bool mixerInitialized;


    // Initializes SDL_mixer if not already initialized
    void initMixer();
};

#endif
