#ifndef SCENE_H
#define SCENE_H

#include "constants/constants.h"
#include "Button/Button.h"

#include <SDL2/SDL.h>
#include <map>
#include <utility>

class Scene{

    private:

        //This map saves the buttons with an asociated string key.
        //A conventional vector would have implicit conventions to locate
        //the buttons if there are a lot, so this way we can eficiently
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


        //MISCELANEOUS

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
        virtual void handleLogic(Uint32 * lastTick, Scene *& curScene);

};

#endif

