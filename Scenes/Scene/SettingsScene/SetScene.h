#ifndef SETSCENE_H
#define SETSCENE_H

#include "Scenes/SceneF/Scene.h"
#include <SDL2/SDL.h>
#include "constants/constants.h"
#include "Scenes/Scenes.h"

class SetScene: public Scene{
    private:
        Scene * mainScene = nullptr;
        SDL_Rect sourceRect = {0,0, SBW, SBH};
        int deltaY;
    public:
        SetScene();
        ~SetScene() override;
        void render() override;
        void handleEvents(SDL_Event event, Scene *& curScene, Scene *& mScene) override;
        void handleLogic(Uint32 *, Scene *&) override;
        void renderButtons(std::map <std::string, Button> map);
        SDL_Rect getSourceRect();
        int getDeltaY();


        void setSourceRect(SDL_Rect rect);
        void setDeltaY(int y);
};

void renderKeyBindChange();

#endif