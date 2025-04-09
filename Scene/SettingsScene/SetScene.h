#ifndef SETSCENE_H
#define SETSCENE_H

#include "Scene/Scene.h"
#include <SDL2/SDL.h>

class SetScene: public Scene{
    private:
    public:
        void update(SDL_Renderer * render) override;
        void render() override;
        void clear(SDL_Renderer * render) override;
};

#endif