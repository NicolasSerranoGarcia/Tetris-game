#ifndef LOOSESCENE_H
#define LOOSESCENE_H

#include "Scene/Scene.h"
#include "constants/constants.h"
#include <SDL2/SDL.h>

class LooseScene: public Scene{
    private:
    public:
        LooseScene();
        void update(SDL_Renderer * render) override;
        void render() override;
        void clear() override;
        void handleEvents(SDL_Event event, Scene *& curScene) override;
};

#endif