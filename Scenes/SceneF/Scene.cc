#include "Scenes/SceneF/Scene.h"

Scene::Scene(){}

Scene::~Scene(){
    name_buttons.clear();
    name_buttons.~map();
}


std::map <std::string, Button>& Scene::getButtonMap(){
    return name_buttons;
}

void Scene::update(SDL_Renderer * render){ 
    SDL_RenderPresent(render);
}

void Scene::renderWithoutFigures(){}

void Scene::clear(){ 
    SDL_SetRenderDrawColor(mainScreen.getRender(), WHITE.r, WHITE.g, WHITE.b, WHITE.a); 
    SDL_RenderClear(mainScreen.getRender()); 
}

void Scene::handleLogic(Uint32 *, Scene *&, Scene *&){}