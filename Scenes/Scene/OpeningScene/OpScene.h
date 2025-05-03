#ifndef OPSCENE_H
#define OPSCENE_H

#include "Scenes/SceneF/Scene.h"
#include "Font/Font.h"
#include "Button/Button.h"
#include "Image/Image.h"
#include "Scenes/Scenes.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

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