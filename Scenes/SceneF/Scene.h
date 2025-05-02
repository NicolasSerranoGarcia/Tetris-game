#ifndef SCENE_H
#define SCENE_H

#include "constants/constants.h"
#include "Button/Button.h"

#include <SDL2/SDL.h>
#include <map>
#include <utility>

class Scene{

    private:
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
        std::map <std::string, Button> getButtonMap();


        //MISCELANEOUS

        virtual void update(SDL_Renderer * render);

        virtual void render() = 0;

        virtual void clear();

        virtual void handleEvents(SDL_Event event, Scene *& curScene, Scene *& mScene) = 0;

        virtual void handleLogic(Uint32 * lastTick, Scene *& curScene) = 0;

};

#endif

