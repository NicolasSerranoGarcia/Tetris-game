#ifndef SETSCENE_H
#define SETSCENE_H

#include "Scenes/SceneF/Scene.h"
#include <SDL2/SDL.h>
#include "constants/constants.h"
#include "Scenes/Scenes.h"

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
        void handleLogic(Uint32 *, Scene *&) override;
};

#endif