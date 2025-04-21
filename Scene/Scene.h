#ifndef SCENE_H
#define SCENE_H

#include <SDL2/SDL.h>
#include "constants/constants.h"

class Scene{
    public:
        Scene();
        virtual ~Scene();
        virtual void update(SDL_Renderer * render);
        virtual void render() = 0;
        virtual void clear();
        virtual void handleEvents(SDL_Event event, Scene *& curScene, Scene *& mScene) = 0;
        virtual void handleLogic(Uint32 * lastTick) = 0;
};

#endif

