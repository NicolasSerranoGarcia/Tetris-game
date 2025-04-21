#ifndef OPSCENE_H
#define OPSCENE_H

#include "Scene/Scene.h"
#include "Font/Font.h"
#include "Button/Button.h"

#include <SDL2/SDL.h>

class OpScene: public Scene{
    private:
    //set the used buttons here
        Button playButton;
    public:
        OpScene();
        void update(SDL_Renderer * render) override;
        void render(Uint32 * lastTick) override;
        void clear() override;
        void handleEvents(SDL_Event event, Scene *& curScene, Scene *& mScene) override;
};

#endif