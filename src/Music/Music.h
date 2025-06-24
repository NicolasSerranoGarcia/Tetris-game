#ifndef MUSIC_H
#define MUSIC_H

#include <string>
#include <SDL2/SDL_mixer.h>
#include <iostream>

class Music {
public:

    // Initializes the SDL_mixer audio system
    //
    // RETURNS:
    // true if initialization was successful, false otherwise
    static bool init();

    // Handles loading a music file (.mp3, .ogg, .wav supported)
    //
    // RETURNS:
    // true if the file was loaded successfully, false otherwise
    bool load(const std::string& filePath);

    // Plays the loaded music
    //
    // RETURNS:
    // true if the music started playing successfully, false otherwise
    bool play(int loops = -1);

    // Pauses the music if it is playing
    void pause();

    // Resumes the music if it is paused
    void resume();

    // Stops the currently playing music
    void stop();

    // Checks if music is currently playing
    //
    // RETURNS:
    // true if music is playing, false otherwise
    bool isPlaying() const;

    // Sets the volume for the music (0 to MIX_MAX_VOLUME)
    void setVolume(int volume);

    // Destructor: frees loaded music
    ~Music();

private:
    Mix_Music* music = nullptr;
};

#endif
