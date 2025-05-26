#include "Sound.h"
#include <iostream>

bool Sound::mixerInitialized = false;

Sound::Sound(const std::string& filePath) : chunk(nullptr), channel(-1) {
    initMixer();
    load(filePath);
}

Sound::Sound() : chunk(nullptr), channel(-1) {
    initMixer();
}

Sound::~Sound() {
    if (chunk) {
        Mix_HaltChannel(channel);
        Mix_FreeChunk(chunk);
    }
}

bool Sound::load(const std::string& filePath) {
    if (chunk) {
        Mix_HaltChannel(channel);
        Mix_FreeChunk(chunk);
        chunk = nullptr;
        channel = -1;
    }

    chunk = Mix_LoadWAV(filePath.c_str());
    if (!chunk) {
        std::cerr << "Failed to load sound: " << Mix_GetError() << "\n";
        return false;
    }

    return true;
}

bool Sound::play() {
    if (!chunk) {
        std::cout << "no chunk";
        return false;
    }

    channel = Mix_PlayChannel(-1, chunk, 0);
    return (channel != -1);
}

bool Sound::pause() {
    if (channel != -1 && Mix_Playing(channel)) {
        Mix_Pause(channel);
        return true;
    }
    return false;
}

bool Sound::resume() {
    if (channel != -1 && Mix_Paused(channel)) {
        Mix_Resume(channel);
        return true;
    }
    return false;
}

bool Sound::stop() {
    if (channel != -1 && Mix_Playing(channel)) {
        Mix_HaltChannel(channel);
        return true;
    }
    return false;
}

bool Sound::isPlaying() const {
    return (channel != -1 && Mix_Playing(channel));
}

void Sound::setVolume(int volume) {
    if (channel != -1) {
        Mix_Volume(channel, volume);
    }
}


void Sound::initMixer() {
    if (!mixerInitialized) {
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
            std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << "\n";
        } else {
            mixerInitialized = true;
        }
    }
}