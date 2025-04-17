#ifndef LOOSESCENE_H
#define LOOSESCENE_H

#include "Scene/Scene.h"
#include "constants/constants.h"
#include <SDL2/SDL.h>

class LooseScene: public Scene{
    private:
    public:
        LooseScene();
        void update(SDL_Renderer * render) override = 0;
        void render(Uint32 * lastTick) override = 0;
        void clear() override = 0;
        void handleEvents(SDL_Event event, Scene *& curScene) override = 0;
};

#endif