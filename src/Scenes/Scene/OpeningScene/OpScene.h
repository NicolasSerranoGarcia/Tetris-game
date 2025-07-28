#ifndef OPSCENE_H
#define OPSCENE_H

//Files for auxiliary classes
#include "src/Font/Font.h"
#include "src/Button/Button.h"
#include "src/Image/Image.h"

//Files for the scenes
#include "src/Scenes/SceneF/Scene.h"
#include "src/Scenes/Scenes.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

//This class is a child. More info on the father class Scene
class OpScene: public Scene{

    public:

        //CONSTRUCTOR

        //Constructor
        OpScene();


        //MISCELLANEOUS

        //This method is an override. To see more info on what
        //it does see the father method. This one renders the
        //play button, and the background image
        //
        //RETURNS:
        //void
        void render() override;

        //This method is an override. To see more info on what
        //it does see the father method. This one handles the play button
        //
        //RETURNS:
        //void
        void handleEvents(SDL_Event event, Scene *& curScene, Scene *& mScene, Sound *) override;

        //Wether if the play button is pressed
        bool isClicked = false;

        //current time since SDL library initialization in ms. Used to preserve across methods
        Uint32 ticks = SDL_GetTicks();

        //if false, the first background sprite will show. Otherwise the second will show
        bool sprite = false;
};

#endif