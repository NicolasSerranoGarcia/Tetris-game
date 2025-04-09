#ifndef OPSCENE_H
#define OPSCENE_H

#include "Scene/Scene.h"
#include "Font/Font.h"
#include "Button/Button.h"

#include <SDL2/SDL.h>

class OpScene: public Scene{
    private:
    public:
        void update(SDL_Renderer * render) override;
        void render() override;
        void clear(SDL_Renderer * render) override;
        void handleEvents(SDL_Event event) override;
};

#endif