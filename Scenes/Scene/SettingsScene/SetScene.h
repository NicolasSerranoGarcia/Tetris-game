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
        void render() override;
        void handleEvents(SDL_Event event, Scene *& curScene, Scene *& mScene) override;
        void handleLogic(Uint32 *, Scene *&) override;
        void renderButtons();
};


#endif