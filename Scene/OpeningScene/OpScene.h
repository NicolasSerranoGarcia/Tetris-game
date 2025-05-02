#ifndef OPSCENE_H
#define OPSCENE_H

#include "Scene/SceneF/Scene.h"
#include "Font/Font.h"
#include "Button/Button.h"

#include <SDL2/SDL.h>

class OpScene: public Scene{
    private:
        Button playButton;
    public:
        OpScene();
        void update(SDL_Renderer * render) override;
        void render() override;
        void clear() override;
        void handleEvents(SDL_Event event, Scene *& curScene, Scene *& mScene) override;
        void handleLogic(Uint32 *, Scene *&) override;
};

#endif