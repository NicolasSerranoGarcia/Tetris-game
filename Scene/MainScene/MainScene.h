#ifndef MAINSCENE_H
#define MAINSCENE_H

#include "Scene/Scene.h"
#include <SDL2/SDL.h>

class MainScene: public Scene{
    private:
    public:
        void update(SDL_Renderer * render) override;
        void render(SDL_Renderer * render) override;
        void clear(SDL_Renderer * render) override;
};

#endif