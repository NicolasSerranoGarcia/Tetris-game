#ifndef MAINSCENE_H
#define MAINSCENE_H

#include "Scene/Scene.h"
#include <SDL2/SDL.h>
#include "constants/constants.h"
#include "Image/Image.h"
#include "Button/Button.h"
#include "Font/Font.h"

class MainScene: public Scene{
    private:
    public:
        void update(SDL_Renderer * render) override;
        void render() override;
        void clear(SDL_Renderer * render) override;
        void handleEvents(SDL_Event event, Scene *& curScene) override;
};

#endif