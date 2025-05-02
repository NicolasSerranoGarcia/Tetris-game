#ifndef MAINSCENE_H
#define MAINSCENE_H

#include "Scene/SceneF/Scene.h"
#include "constants/constants.h"
#include "Image/Image.h"
#include "Button/Button.h"
#include "Font/Font.h"
#include "Figures/Block/Block.h"
#include "Figures/FigureF/Figure.h"
#include "Scene/Scenes.h"
#include "Figures/Figures.h" //This is just all the header file figures in a single file

#include <SDL2/SDL.h>

class MainScene: public Scene{
    private:
        Button settingsButton;
        std::vector <Figure*> gameBoard;
        Figure* currentFigure = nullptr;
        Figure * nextFigures[3] = {nullptr};
        bool dead = false;
        bool spaceBarPressed = false;
    public:
        MainScene();
        void update(SDL_Renderer * render) override;
        void render() override;
        void clear() override;
        void handleEvents(SDL_Event event, Scene *& curScene, Scene *& mScene) override;
        void handleLogic(Uint32 * lastTick, Scene *& curScene) override;
        Figure * getCurrentFigure();
};

void getRandomFigure(Figure *& curFigure, Figure * lastFigs[]);
void getRandomFigure(Figure *& Figure);
void fetchNextFigure(Figure *& curFigure, Figure * nextFigs[]);
bool colides(std::vector <Figure*> gameBoard, SDL_Keycode key, Figure *& curFigure);
void renderNextFigures(Figure * nextFigs[], int nextBgH);
bool isDead(std::vector <Figure*> gameBoard);


#endif