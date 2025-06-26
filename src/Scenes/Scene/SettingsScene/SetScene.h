#ifndef SETSCENE_H
#define SETSCENE_H

#include "src/Scenes/SceneF/Scene.h"
#include "src/constants/constants.h"
#include "src/Scenes/Scenes.h"
#include "src/Slider/Slider.h"
#include "src/Sound/Sound.h"

#include <SDL2/SDL.h>

//This struct saves a combination of a button and
//a boolean. The boolean tells wether the button is being
//pressed right now
struct ButClick{
    Button button;
    bool clicked;
};

//This class is a child. More info on the father class Scene
class SetScene: public Scene{

    private:

        //This pointer saves the mainScene pointer that comes
        //as an argument from the handleEvents() method inside
        //the class. It's purpose is to call renderWithoutFigures()
        //method from inside the render() method, nothing else
        Scene * mainScene = nullptr;

        //This is the button that shows on the upper left edge of the
        //settings and that goes back to the mainScene.
        Button exitButton;

        //This map is used to store a combination of key button pairs.
        //This map only saves the buttons of the keybinds. 
        std::map <std::string, ButClick> mapButtonPressed;

        //This vector saves all the keys used to locate the buttons inside the
        //maps used in the class. It is loaded in the constructor
        std::vector <std::string> keys;

        //Has any button of the keybinds been pressed before? When a keybind button
        //gets pressed, the user can still click other things like sliders, buttons
        //so, this variable keeps track if a keybind button is waiting for a key
        //to be pressed
        bool anyButtonPressed = false;

        //This rectangle is the square that acts as a "window" of the settings texture.
        //You can look at documentation for explanation. It will change it's y pos
        //when the user scrolls
        SDL_Rect sourceRect = {0,0, SETTINGSBACKGROUNDW, SETTINGSBACKGROUNDH};

        //This is the slider tht appears on the right of the settings. It can be clicked
        //and then moved to scroll through the settings
        Slider settingsSlider;

        //This is the slider that is used to control the general (music) volume in the settings.
        //It can be found scrolling through the settings. It has an associated logic slider
        //(see documentation for explanation)
        Slider soundSlider;
        Slider LogicSoundSlider;

        //This is the slider that is used to control the effects volume in the settings.
        //It can be found scrolling through the settings. It has an associated logic slider
        //(see documentation for explanation)
        Slider effectsSlider;
        Slider LogicEffectsSlider;

        Button linktree;
        Button linktreeLogic;
        ButClick linktrr;

        Button github;
        Button githubLogic;
        ButClick git;

        Button instagram;
        Button instagramLogic;
        ButClick insta;

        Button stopMusic;
        Button stopMusicLogic;
        ButClick stp;

        Button goBackMusic;
        Button goBackMusicLogic;
        ButClick goBck;

        Button goForwardMusic;
        Button goForwardMusicLogic;
        ButClick goFor;

        bool isStoped = false;

        //This is the sound associated with opening the settings
        Sound open;

        //This is the sound associated with clicking a button
        Sound ButtonClick;

        //This is the sound associated with the countdown
        //when closing the settings scene. 
        Sound countdown;

    public:

        SetScene();

        ~SetScene() override;

        
        SDL_Rect getSourceRect();

        
        void setSourceRect(SDL_Rect rect);
        
        
        void handleLogic(Uint32 *, Scene *&, Scene *&) override;

        void handleEvents(SDL_Event event, Scene *& curScene, Scene *& mScene, Sound * music) override;

        void renderAllButtons(std::map <std::string, Button> map);

        void render() override;

        void renderButton(Button button);


    };
    
    void renderKeyBindChange(Button button, SetScene & s);
    
    SDL_Keycode& getKeyBindByKey(std::string key);

    const char * getMessageByKey(std::string key);
    
    int getXposFromSoundLvl(int minX);

    int getXposFromEffectsLvl(int minX);

#endif
