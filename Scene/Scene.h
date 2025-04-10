#ifndef SCENE_H
#define SCENE_H

#include <SDL2/SDL.h>
#include "constants/constants.h"

class Scene{
    public:
        virtual void update(SDL_Renderer * render){ SDL_RenderPresent(render); };
        virtual void render() = 0;
        virtual void clear(SDL_Renderer * render){ SDL_SetRenderDrawColor(mainScreen.getRender(), BLACK.r, BLACK.g, BLACK.b, BLACK.a); SDL_RenderClear(render); };
        virtual void handleEvents(SDL_Event event, Scene *& curScene) = 0;
};

#endif

