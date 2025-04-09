#include "OpScene.h"

#include <iostream>
#include <SDL2/SDL_image.h>

//this function is inherited and the normal case is that it doesn't need any further coding. Still, at the moment I'm gonna call the father method from the child one in case 
//I need to make extra implementations
void OpScene::update(SDL_Renderer * render){
    Scene::update(render);
    //I'll probably place something here hehe
}

void OpScene::render(){
    //All the implementation of the scene is going here. 
    Font Title(&mainScreen, "BungeeTint-Regular", 90, "TETRIS", RED);
    Font Play(&mainScreen, "Ubuntu-Bold", 60, "PLAY", BLACK);
    Button playButton({px(Rposition::POS_CENTER_DOWN, 160), py(Rposition::POS_CENTER_LEFT, 70), 160, 70}, WHITE, &mainScreen);
    playButton.setFont(&Play);
    SDL_Texture * texture = IMG_LoadTexture(mainScreen.getRender(), "IMG/OpScene-background.png");
    SDL_Rect destRect = {0, 0, mainScreen.getWidth(), mainScreen.getHeight()};
    SDL_RenderCopy(mainScreen.getRender(), texture, NULL, &destRect);

    Title.drawTextToRender(Rposition::POS_CENTER_UP);
    playButton.drawToRender();
    SDL_RenderPresent(mainScreen.getRender());

}

void OpScene::clear(SDL_Renderer * render){
    Scene::clear(render);
    //""
}

void OpScene::handleEvents(SDL_Event event){
    Button playButton({px(Rposition::POS_CENTER_DOWN, 160), py(Rposition::POS_CENTER_LEFT, 70), 160, 70}, WHITE, &mainScreen);
    if(playButton.isClicked(&event)){
        std::cout << "Hello World" << std::endl;
    }
}