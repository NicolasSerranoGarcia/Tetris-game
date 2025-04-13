#ifndef SETSCENE_H
#define SETSCENE_H

#include "Scene/Scene.h"
#include <SDL2/SDL.h>
#include "constants/constants.h"

class SetScene: public Scene{
    private:
    public:
        ~SetScene();
        SetScene();
        void update(SDL_Renderer * render) override;
        void render() override;
        void clear() override;
        void handleEvents(SDL_Event event, Scene *& curScene) override;
};

#endif