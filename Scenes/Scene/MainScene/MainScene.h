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
#include <random>


//This class is a child. More info on the father class Scene
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

        //This pointer points to the figure that the player is holding (the saved one)
        //Whenever the player presses the correct key (check the settings), the current figure
        //will be swapped with the holded one, and the player now will be able to save it.
        //There's a max of 2 swaps, meaning the saw key can be pressed two times per falling figure.
        //Another important thing to mention is that the figure that is swapped will appear 2 blocks above
        //the previous one
        Figure * holdedFigure = nullptr;

        //This variable saves the number of times a figure has been swapped. It resets each time
        //a figure is placed
        int numberSwaps = 0;
        
        //Player looses ? => dead = true
        bool dead = false;
        
    public:   
    
        //CONSTRUCTORS/DESTRUCTOR
        
        //Cnstructor
        MainScene();
        
        //Destructor. Also calls the father destructor Scene::~Scene()
        ~MainScene() override;
    

        //GETTERS

        //Getter
        //
        //RETURNS:
        //a pointer to the current figure
        Figure * getCurrentFigure() const;

        //Getter
        //
        //RETURNS:
        //a pointer to the array of next figures
        Figure ** getNextFigures();

        //Getter
        //
        //RETURNS:
        //a reference to the vector of figures (gameboard)
        std::vector <Figure*>& getGameBoard();


        //SETTERS

        //Setter
        //
        //RETURNS:
        //void
        void setNumSwaps(int swap);

        //MISCELLANEOUS

        //This method is an override. To see more info on what
        //it does see the father method. This one renders the
        //play scene, the points, the figures, the background rectangles...
        //
        //RETURNS:
        //void
        void render() override;

        //This method is an override, but it is unique to the class
        //MainScene. It does the same as render() but without the figures.
        //By figures I mean the gameboard, the current figure and the next figures
        //
        //RETURNS:
        //void
        void renderWithoutFigures() override;


        //This method is an override. To see more info on what
        //it does see the father method. This one handles the settings button and the
        //controls (left, down, rotate...)
        //
        //
        //RETURNS:
        //void
        void handleEvents(SDL_Event event, Scene *& curScene, Scene *& mScene) override;

        //This method is an override. To see more info on what
        //it does see the father method. This one handles the automatic figure drop
        //and line clearing
        //
        //
        //RETURNS:
        //void
        void handleLogic(Uint32 * lastTick, Scene *& curScene) override;

        //This method handles the death of the user. It is called at the end of methods
        //that can trigger a death case. It switches the scene to a new one in case the
        //user dies
        //
        //RETURNS:
        //void
        void handleDeath(Scene *& curScene);

};


//FUNCTIONS

//This function loads the figure passed as a parameter with a new, random figure
//
//RETURNS:
//void
void getRandomFigure(Figure *& Figure);

//This function loads the figure passed as a parameter with a new, random figure.
//It update it with a figure distinct from the last 3. The second parameter
//represents this concept
//
//RETURNS:
//void
void getRandomFigure(Figure *& curFigure, Figure * lastFigs[]);

//This function fetches the next figure from the next figures array. In the process it calls
//getRandomFigure(). At the end the next figures array will be updated with a new figure at
//the end of it. See the documentation for more info
//
//RETURNS:
//void
void fetchNextFigure(Figure *& curFigure, Figure * nextFigs[]);

//This function returns true if the figure passed as a parameter colides with any of the figures
//of the gameboard. 
//NOTE: Keep in mind that the figure will be checked with a movement. That is,
//the function checks if the figure colides IN THE CASE the figure is moved in the way that
//the "key" parameter dictates. 
//
//RETURNS:
//-true if the function colides
//-false in any other case. It will also return false if the parameter passed as "key" is not
//one of the game keys. The current game keys that need collision checking are rotate, 
//move left, move right and move down.
bool colides(std::vector <Figure*> gameBoard, SDL_Keycode key, Figure * const & curFigure);

//This function returns true if the figure passed as a parameter colides with any of the figures
//of the gameboard. 
//NOTE: This function, unlike colides(), checks if the figure colides in it's current position (no 
//movement in advance). This function also checks collision with the borders
//
//RETURNS:
//-true if the function colides
//-false in any other case
bool colidesStatic(std::vector <Figure*> gameBoard, Figure * const &figure);

//This function handles the mechanic of the fast drop. The figure passed as a parameter will be
//updated as if it was "dropped" until the lowest possible point without coliding with another
//figure or the grid. 
//NOTE: If the event passed as a parameter is not the CONTROLFASTDOWN one, the function won't do 
//anything
//
//RETURNS:
//void
void handleFastDrop(SDL_Event event, Figure*& figure, MainScene& m);

//This function renders the next 3 figures in it's box. It takes the next figures array as a parameter
//
//RETURNS:
//void
void renderNextFigures(Figure * nextFigs[], int nextBgH);

//This function checks wether if the current state of the game is a death point. This function will not
//interfere with any atribute of the class. It will normally be called as a condition for something else.
//
//RETURNS:
//-false if the user is not dead
//-true otherwise
bool isDead(std::vector <Figure*> gameBoard);

//This function takes all the info necesary to swap a figure when the swap key is pressed. Notice that the function does not check if the key pressed
//is the swap key. Therefore this function should be called when we WANT to swap a figure. There's also no check for the number of times a figure is swapped.
//All of this is left asside of the function.
//
//RETURNS:
//void
void handleSwap(Figure *& fallingFigure, Figure *& holdedFigure, Figure * nextFigs[], int * numSwaps, std::vector <Figure*> gameBoard);

//This function places the holded figure in it's corresponding sqaure in the screen. This is just a function to change the position of the holded figure
//so that it is rendered on the correct position
//
//RETURNS:
//void
void changeSwappedFigurePosition(Figure *& holdedFigure);

#endif