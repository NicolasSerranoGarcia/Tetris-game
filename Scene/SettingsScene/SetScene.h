#ifndef SETSCENE_H
#define SETSCENE_H

#include "Scene/Scene.h"
#include <SDL2/SDL.h>
#include "constants/constants.h"
#include "Scene/Scenes.h"

class SetScene: public Scene{
    private:
        Scene * mainScene = nullptr;
    public:
        SetScene();
        ~SetScene() override;
        void update(SDL_Renderer * render) override;
        void render() override;
        void clear() override;
        void handleEvents(SDL_Event event, Scene *& curScene, Scene *& mScene) override;
        void handleLogic(Uint32 * lastTick, Scene *& curScene) override;
};

#endif