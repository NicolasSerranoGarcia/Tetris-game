#ifndef SOUND_H
#define SOUND_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>

//This Handles loading and controlling a single sound (MP3 supported)
class Sound {
    
    private:

    //Pointer to the loaded sound chunk
    Mix_Chunk* chunk;

    //Channel number used to play this sound
    int channel;

    //Whether SDL_mixer has been initialized globally
    static bool mixerInitialized;

    //Initializes SDL_mixer if not already initialized
    void initMixer();

    public:
    
        //CONSTRUCTORS/DESTRUCTOR

        //Constructor
        Sound(const std::string& filePath);
    
        //Constructor
        Sound();
    
        //Destructor
        ~Sound();
    

        //MISCELLANEOUS

        //Loads a sound file
        //
        //RETURNS:
        //true if loading succeeded
        //false otherwise
        bool load(const std::string& filePath);
    
        //Plays the sound from the beginning
        //
        //RETURNS:
        //True if playback started, false otherwise
        bool play();
    
        //Pauses the currently playing sound
        //
        //RETURNS:
        //True if the sound was paused, false otherwise
        bool pause();
    
        //Resumes playback if the sound was paused
        //
        //RETURNS:
        //true if resumed
        //false otherwise
        bool resume();
    
        //Stops the currently playing sound
        //
        //RETURNS:
        //true if the sound was stopped
        //false otherwise
        bool stop();
    
        //Checks if the sound is currently playing
        //
        //RETURNS:
        //true if playing
        //false otherwise
        bool isPlaying() const;
    
        //Sets the volume for this sound instance
        //
        //volume: 0 (mute) to 128 (max)
        //RETURNS: void
        void setVolume(int volume);
        
};

#endif
