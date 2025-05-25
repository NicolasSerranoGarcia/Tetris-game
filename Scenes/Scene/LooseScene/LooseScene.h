#ifndef LOOSESCENE_H
#define LOOSESCENE_H

#include "Scenes/SceneF/Scene.h"
#include "Scenes/Scenes.h"
#include "constants/constants.h"
#include <SDL2/SDL.h>

class LooseScene: public Scene{
    private:
        Scene * mainScene = nullptr;
    public:
        LooseScene();
        void render() override;
        void handleEvents(SDL_Event event, Scene *& curScene, Scene *& mScene) override;
        void handleLogic(Uint32 *, Scene *&, Scene *&) override;
};

#endif