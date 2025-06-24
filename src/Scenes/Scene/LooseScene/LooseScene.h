#ifndef LOOSESCENE_H
#define LOOSESCENE_H

#include "src/Scenes/SceneF/Scene.h"
#include "src/Scenes/Scenes.h"
#include "src/constants/constants.h"

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