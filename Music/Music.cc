#include "Music.h"

bool Music::init() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer could not initialize: " << Mix_GetError() << "\n";
        return false;
    }

    return true;
}

bool Music::load(const std::string& filePath) {
    if (music) {
        Mix_FreeMusic(music);
        music = nullptr;
    }

    music = Mix_LoadMUS(filePath.c_str());
    if (!music) {
        std::cerr << "Failed to load music: " << Mix_GetError() << "\n";
        return false;
    }

    return true;
}

bool Music::play(int loops) {
    if (!music) return false;

    if (Mix_PlayMusic(music, loops) == -1) {
        std::cerr << "Failed to play music: " << Mix_GetError() << "\n";
        return false;
    }

    return true;
}

void Music::pause() {
    if (Mix_PlayingMusic()) {
        Mix_PauseMusic();
    }
}

void Music::resume() {
    if (Mix_PausedMusic()) {
        Mix_ResumeMusic();
    }
}

void Music::stop() {
    Mix_HaltMusic();
}

bool Music::isPlaying() const {
    return Mix_PlayingMusic() != 0;
}

void Music::setVolume(int volume) {
    Mix_VolumeMusic((int) (128*volume/100));
}

Music::~Music() {
    if (music) {
        Mix_FreeMusic(music);
        music = nullptr;
    }
}
