#ifndef LOOSESCENE_H
#define LOOSESCENE_H

#include "src/Scenes/SceneF/Scene.h"
#include "src/Scenes/Scenes.h"
#include "src/constants/constants.h"

#include <SDL2/SDL.h>

class LooseScene: public Scene{
    private:

        //This pointer is used to render the mainScene as a background (like 
        //in the settings scene)
        Scene * mainScene = nullptr;

        //is the play button currently clicked?
        //Used for rendering different textures
        bool isPlayClicked = false;

        //is the return to opScene button currently clicked?
        //Used for rendering different textures
        bool isReturnClicked = false;

        //is the settings button currently clicked?
        //Used for rendering different textures
        bool isSettingsClicked = false;

    public:

        //CONSTRUCTORS/DESTRUCTOR

        //Constructor
        LooseScene();

        //Destructor
        ~LooseScene();


        //MISCELLANEOUS

        //This method is an override. To see more info on what
        //it does see the father method. This one renders the
        //buttons, the mainScene background
        //
        //RETURNS:
        //void
        void render() override;

        //This method is an override. To see more info on what
        //it does see the father method. This one handles the clicking
        //of the buttons
        //
        //
        //RETURNS:
        //void
        void handleEvents(SDL_Event event, Scene *& curScene, Scene *& mScene, Sound *) override;

        //This method is an override. To see more info on what
        //it does see the father method. This one is used to copy the mainScene
        //pointer that is passed as a parameter to the class attribute
        //
        //
        //RETURNS:
        //void
        void handleLogic(Uint32 *, Scene *&, Scene *&) override;
};

#endif