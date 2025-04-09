#ifndef SCENE_H
#define SCENE_H

#include <SDL2/SDL.h>

class Scene{
    public:
        virtual void update(SDL_Renderer * render){ SDL_RenderPresent(render); };
        virtual void render() = 0;
        virtual void clear(SDL_Renderer * render){ SDL_RenderClear(render); };
        virtual void handleEvents(SDL_Event event) = 0;
};

#endif

