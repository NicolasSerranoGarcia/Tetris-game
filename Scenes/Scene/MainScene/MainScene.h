#ifndef MAINSCENE_H
#define MAINSCENE_H

#include "constants/constants.h"

//FIles for auxilary clases
#include "Image/Image.h"
#include "Button/Button.h"
#include "Font/Font.h"

//Files for the scenes
#include "Scenes/SceneF/Scene.h"
#include "Scenes/Scenes.h"

//Files for the figures
#include "Figures/Block/Block.h"
#include "Figures/FigureF/Figure.h"
#include "Figures/Figures.h"

#include <SDL2/SDL.h>

class MainScene: public Scene{

    private:

        //This vector saves the pointer to the figures that are placed in the game.
        //Notice that each figure has it's own unique pointer. Another thing to mention
        //is that, if we have a figure falling and we place it, the only reference to that
        //figure will be the pointer inside this vector from that point on. We don't have 
        //a way to get an exact figure from this vector (we don't have id' or keys for the figures)
        std::vector <Figure*> gameBoard;

        //This pointer points to the figure that the player is currently controling.
        //Whenever a figure is placed, the reference to the figure will be moved to the figures vector,
        //and this pointer will point to a newly created figure. Notice that in this process the 
        //figure is NOT deleted (but this pointer no longer references it)
        Figure* currentFigure = nullptr;

        //This array saves the next 3 figures that will be fetched to the gameboard. Whenever
        //a figure is placed, the pointer to the current figure will be replaced with nextFigures[0]
        //and this array will loose the reference to that figure. A reference to a newly created figure
        //will be placed in nextFigures[2]. Of course nextFigures[0] will now be the previous nextFigures[1]
        //and so on
        Figure * nextFigures[3] = {nullptr};

        //Player looses ? => dead = true
        bool dead = false;

        //This boolean is used to check wether if the user is mantaining the spacebar key
        bool spaceBarPressed = false;

        //This boolean is used to check wether if the user is mantaining the rotate key
        bool rotateKeyPressed = false;

    public:

        //CONSTRUCTORS/DESTRUCTOR

        //Cnstructor
        MainScene();

        //Destructor. Also calls the father desructor
        ~MainScene() override;


        //MISCELLANEOUS

        //This method is an override. To see more info on what
        //it does see the father method. This one renders the
        //play scene, the points, the figures, the background rectangles...
        //
        //RETURNS:
        //void
        void render() override;

        //This method is an override. To see more info on what
        //it does see the father method. This one handles the settings button,
        //
        //
        //RETURNS:
        //void
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