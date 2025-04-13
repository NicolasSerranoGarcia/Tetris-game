#ifndef MAINSCENE_H
#define MAINSCENE_H

#include "Scene/Scene.h"
#include <SDL2/SDL.h>
#include "constants/constants.h"
#include "Image/Image.h"
#include "Button/Button.h"
#include "Font/Font.h"
#include "Figures/Block/Block.h"
#include "Figures/Figure.h"

class MainScene: public Scene{
    private:
        Button settingsButton;
        Block gameBoard[20][10]; //static array bc I don't need any resize and I'm more comfortabe dealing with static arrays :)
        Figure *currentFigure;
    public:
        MainScene();
        void update(SDL_Renderer * render) override;
        void render() override;
        void clear(SDL_Renderer * render) override;
        void handleEvents(SDL_Event event, Scene *& curScene) override;
};

#endif