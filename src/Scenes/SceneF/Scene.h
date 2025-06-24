#ifndef SCENE_H
#define SCENE_H

#include "src/constants/constants.h"
#include "src/Button/Button.h"

#include <SDL2/SDL.h>
#include <map>
#include <utility>

//This father class implements a dynamic way to handle the game state. The basic functioning
//of the program is to switch between scenes triggered by user interaction. The whole program
//consists of a combination of scenes that change depending on this input. Every child implements
//it's own methods for rendering the scene, handling the events that come from the user and, depending
//on the complexity of the scene, other methods like handling the logic. Except special cases, whenever
//a scene is switched, the scene that was showing will be deleted. This means that the instance of the 
//child scene will be deleted. If the user invokes the scene again, a new instance will be created. 
//For more info see the documentation
class Scene{

    private:

        //This map saves the buttons with an associated string key.
        //A conventional vector would have implicit conventions to locate
        //the buttons if there are a lot, so this way we can efficiently
        //use the string keys to get the desired button
        std::map <std::string, Button> name_buttons;

    public:

        //CONSTRUCTORS/DESTRUCTOR

        //Constructor
        Scene();

        //Destructor
        virtual ~Scene();


        //GETTERS

        //Getter
        //
        //RETURNS:
        //The map saving all the buttons 
        virtual std::map <std::string, Button>& getButtonMap();


        //MISCELLANEOUS

        //This method shows the scene by calling SDL_RenderPresent()
        //
        //RETURNS:
        //void
        virtual void update(SDL_Renderer * render);

        //This method is handled individually by the child classes.
        //Normally you will find all the visual elements of the scene
        // get rendered here (for example rendering the figures)
        //
        //RETURNS:
        //void
        virtual void render() = 0;

        //This method is specific for MainScene. It does the same as 
        //Scene::Render(), but without rendering the figures (all of them)
        //
        //RETURNS:
        //void
        virtual void renderWithoutFigures();

        //This method clears the scene by calling SDL_RenderClear()
        //
        //RETURNS:
        //void
        virtual void clear();

        //This method is handled individually by the child classes.
        //Normally you will find all the event-related elements
        //of the scene get processed here (for example checking
        //if a button is clicked)
        //
        //RETURNS:
        //void
        virtual void handleEvents(SDL_Event event, Scene *& curScene, Scene *& mScene) = 0;

        //This method is specially created for the mainScene child,
        //which has a lot of gameplay load. In this method you will 
        //find tasks like handing specific objects of the scene 
        //(like the figures in the case of mainScene)
        //
        //RETURNS:
        //void
        virtual void handleLogic(Uint32 * lastTick, Scene *& curScene, Scene *& mScene);

};

#endif

