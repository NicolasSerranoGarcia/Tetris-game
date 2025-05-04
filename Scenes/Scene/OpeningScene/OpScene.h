#ifndef OPSCENE_H
#define OPSCENE_H

//Files for auxiliary classes
#include "Font/Font.h"
#include "Button/Button.h"
#include "Image/Image.h"

//Files for the scenes
#include "Scenes/SceneF/Scene.h"
#include "Scenes/Scenes.h"

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
        void handleEvents(SDL_Event event, Scene *& curScene, Scene *& mScene) override;

};

#endif