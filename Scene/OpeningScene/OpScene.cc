#include "OpScene.h"

#include <iostream>
#include <SDL2/SDL_image.h>
#include "Image/Image.h"
#include "Scene/Scenes.h"

//this function is inherited and the normal case is that it doesn't need any further coding. Still, at the moment I'm gonna call the father method from the child one in case 
//I need to make extra implementations
void OpScene::update(SDL_Renderer * render){
    Scene::update(render);
    //I'll probably place something here hehe
}

void OpScene::render(){
    //All the implementation of the scene is going here. 

    //Load the background image
    Image background(0, 0, mainScreen.getWidth(), mainScreen.getHeight(), "OpScene-background");
    background.CopyToRender();
    //Load the title and the play button
    Font Title(&mainScreen, "BungeeTint-Regular", 90, "TETRIS", RED);
    Font Play(&mainScreen, "Ubuntu-Bold", 60, "PLAY", BLACK);
    Button playButton({px(AbsPosition::POS_CENTER_DOWN, 160), py(AbsPosition::POS_CENTER_LEFT, 70), 160, 70}, GREEN, &mainScreen);



    Button settingsButton(0, 0, 70, 70, WHITE, &mainScreen);
    playButton.setFont(&Play);
    
    Title.drawTextToRender(AbsPosition::POS_CENTER_UP);
    playButton.drawToRender();
    
    settingsButton.setRelativeTo(playButton, RPosition::POS_REL_RIGHT);
    
    //load an image of settings
    Image settingsImage(settingsButton.getContainer().x, settingsButton.getContainer().y, settingsButton.getContainer().w, settingsButton.getContainer().h, "OpScene-settings");
    
    //pass it to the button
    settingsButton.setImage(&settingsImage);

    //draw the settings buton with the image
    settingsButton.drawToRender();
    SDL_RenderPresent(mainScreen.getRender());

}

void OpScene::clear(SDL_Renderer * render){
    Scene::clear(render);
    //""
}

//ERROR: right now I don't know why changing the lobal pointer is not working. Anyways I will find a way
void OpScene::handleEvents(SDL_Event event, Scene *& curScene){
    Button playButton({px(AbsPosition::POS_CENTER_DOWN, 160), py(AbsPosition::POS_CENTER_LEFT, 70), 160, 70}, WHITE, &mainScreen);
    if(playButton.isClicked(&event)){
        std::cout << "Play" << std::endl; 
        //curScene = new MainScene;
    }

    Button settingsButton(0, 0, 70, 70, WHITE, &mainScreen);
    settingsButton.setRelativeTo(playButton, RPosition::POS_REL_RIGHT);
    if(settingsButton.isClicked(&event)){
        std::cout << "Settings" << std::endl;
    }
}