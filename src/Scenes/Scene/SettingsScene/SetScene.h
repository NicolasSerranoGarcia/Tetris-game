#ifndef SETSCENE_H
#define SETSCENE_H

#include "src/Scenes/SceneF/Scene.h"
#include "src/constants/constants.h"
#include "src/Scenes/Scenes.h"
#include "src/Slider/Slider.h"
#include "src/Sound/Sound.h"

#include <SDL2/SDL.h>

struct ButClick{
    Button button;
    bool clicked;
};

//This class is a child. MOre info on the father class Scene
class SetScene: public Scene{

    private:

        Scene * mainScene = nullptr;

        Button exitButton;

        std::map <std::string, ButClick> mapButtonPressed;
        std::vector <std::string> keys;

        bool anyButtonPressed = false;

        SDL_Rect sourceRect = {0,0, SETTINGSBACKGROUNDW, SETTINGSBACKGROUNDH};

        Slider settingsSlider;

        Slider soundSlider;
        Slider LogicSoundSlider;

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

        Sound open;

        Sound ButtonClick;

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
