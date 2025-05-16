#ifndef SETSCENE_H
#define SETSCENE_H

#include "Scenes/SceneF/Scene.h"
#include <SDL2/SDL.h>
#include "constants/constants.h"
#include "Scenes/Scenes.h"
#include "Slider/Slider.h"

struct ButClick{
    Button button;
    bool clicked;
};

//This class is a child. MOre info on the father class Scene
class SetScene: public Scene{

    private:

        Scene * mainScene = nullptr;

        SDL_Rect sourceRect = {0,0, SETTINGSBACKGROUNDW, SETTINGSBACKGROUNDH};

        int deltaY;

        std::map <std::string, ButClick> mapButtonPressed;

        bool anyButtonPressed = false;

        Slider rightSlider;

        std::vector <std::string> keys;

    public:

        SetScene();

        ~SetScene() override;

        
        SDL_Rect getSourceRect();

        int getDeltaY();
        
        
        void setSourceRect(SDL_Rect rect);
        
        void setDeltaY(int y);
        
        
        void handleLogic(Uint32 *, Scene *&) override;

        void handleEvents(SDL_Event event, Scene *& curScene, Scene *& mScene) override;

        void renderButtons(std::map <std::string, Button> map);

        void render() override;

        void renderButton(Button button);


    };
    
    void renderKeyBindChange(Button button, SetScene & s);
    
    SDL_Keycode getKeyBindByKey(std::string key);

    const char * getMessageByKey(std::string key);

#endif