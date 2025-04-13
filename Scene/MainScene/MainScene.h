#ifndef MAINSCENE_H
#define MAINSCENE_H

#include "Scene/Scene.h"
#include "constants/constants.h"
#include "Image/Image.h"
#include "Button/Button.h"
#include "Font/Font.h"
#include "Figures/Block/Block.h"
#include "Figures/Figure.h"
#include "Scene/SettingsScene/SetScene.h"

#include <SDL2/SDL.h>

class MainScene: public Scene{
    private:
        Button settingsButton;
        std::vector <Figure*> gameBoard;
        Figure* currentFigure = nullptr;
    public:
        MainScene();
        void update(SDL_Renderer * render) override;
        void render() override;
        void clear() override;
        void handleEvents(SDL_Event event, Scene *& curScene) override;
        Figure * getCurrentFigure();
};

void getRandomFigure(Figure *& curFigure);

#endif