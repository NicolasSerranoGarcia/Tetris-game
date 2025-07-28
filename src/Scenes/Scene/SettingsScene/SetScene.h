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

        //The associated logic slider of effectsSlider
        Slider LogicEffectsSlider;

        //This is the button that leads to my linktree in the settings
        Button linktree;
        Button linktreeLogic;
        ButClick linktrr;

        //This is the button that leads to my github in the settings
        Button github;

        //The associated logic button of github button
        Button githubLogic;
        ButClick git;

        //This is the button that leads to my instagram in the settings
        Button instagram;

        //The associated logic button of instagram button
        Button instagramLogic;
        ButClick insta;


        //This is the button that stops the music in the settings
        Button stopMusic;

        //The associated logic button of stopMusic button
        Button stopMusicLogic;
        ButClick stp;

        //This is the button that rewinds the music in the settings
        Button goBackMusic;

        //The associated logic button of goBackMusic button
        Button goBackMusicLogic;
        ButClick goBck;

        //This is the button that skips the music in the settings
        Button goForwardMusic;

        //The associated logic button of goForwardMusic button
        Button goForwardMusicLogic;
        ButClick goFor;

        //This is the button that exits the settings
        Button exit;

        //The associated logic button of exit button
        Button exitLogic;
        ButClick ext;

        //is the music stopped right now? It is used to switch
        //the texture of the stop/continue button
        bool isStoped = false;


        //This is the sound associated with opening the settings
        Sound open;

        //This is the sound associated with clicking a button
        Sound ButtonClick;

        //This is the sound associated with the countdown
        //when closing the settings scene. 
        Sound countdown;

    public:

        //CONSTRUCTORS/DESTRUCTOR

        //Constructor
        SetScene();

        //Destructor
        ~SetScene() override;


        //GETTERS

        //Getter
        //
        //RETURNS:
        //an SDL_Rect instance representing the source
        //rectangle (see documentation)
        SDL_Rect getSourceRect();


        //SETTERS

        //Setter
        //
        //RETURNS:
        //void
        void setSourceRect(SDL_Rect rect);
        

        //MISCELLANEOUS

        //This method is an override. To see more info on what
        //it does see the father method. This one renders the
        //buttons, sliders, the settings texture...
        //
        //RETURNS:
        //void
        void render() override;

        //This method is an override. To see more info on what
        //it does see the father method. This one handles the clicking
        //of the buttons, sliders, the linking of the socials of the buttons
        //the scrolling...
        //
        //
        //RETURNS:
        //void
        void handleEvents(SDL_Event event, Scene *& curScene, Scene *& mScene, Sound * music) override;

        //This method renders all the key bind buttons in it's correct place
        //
        //RETURNS:
        //void
        void renderAllButtons(std::map <std::string, Button> map);

        //This method renders a single key bind button in it's correct place
        //
        //RETURNS:
        //void
        void renderButton(Button button);

    };


    //FUNCTIONS
    
    //This function render an overlay to the keybind button that is clicked right now
    //This overlay is shown until the user presses a key or clicks another key bind 
    //button
    //
    //RETURNS:
    //void
    void renderKeyBindChange(Button button, SetScene & s);
    
    //This method returns a reference to the associated SDL_Keycode variable action.
    //The parameter key represents the key used in the maps of the class to identify
    //the button. 
    //
    //RETURNS:
    //A reference to an SDL:Keycode instance
    SDL_Keycode& getKeyBindByKey(std::string key);

    //This method returns a dialog text that is used to show a text so that the user
    //what does the key bind button do
    //
    //RETURNS:
    //A const char pointer 
    const char * getMessageByKey(std::string key);
    
    //This method converts the current sound level into the X position of the slider
    //
    //RETURNS:
    //An integer representing the X position of the sound slider
    int getXposFromSoundLvl(int minX);

    //This method converts the current effects level into the X position of the slider
    //
    //RETURNS:
    //An integer representing the X position of the effects slider
    int getXposFromEffectsLvl(int minX);

#endif
