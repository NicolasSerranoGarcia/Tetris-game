#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

int main() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL_Init error: " << SDL_GetError() << std::endl;
        return 1;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "Mix_OpenAudio error: " << Mix_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    Mix_AllocateChannels(16);

    Mix_Chunk* chunk = Mix_LoadWAV("explosion.wav");
    if (!chunk) {
        std::cerr << "Mix_LoadWAV error: " << Mix_GetError() << std::endl;
        Mix_CloseAudio();
        SDL_Quit();
        return 1;
    }

    int channel = Mix_PlayChannel(-1, chunk, 0);
    if (channel == -1) {
        std::cerr << "Mix_PlayChannel error: " << Mix_GetError() << std::endl;
    }

    SDL_Delay(2000);

    Mix_FreeChunk(chunk);
    Mix_CloseAudio();
    SDL_Quit();

    return 0;
}
