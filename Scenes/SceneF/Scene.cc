#include "Scenes/SceneF/Scene.h"

Scene::Scene(){};

Scene::~Scene(){};

void Scene::update(SDL_Renderer * render){ 
    SDL_RenderPresent(render);
}
void Scene::clear(){ 
    SDL_SetRenderDrawColor(mainScreen.getRender(), BLACK.r, BLACK.g, BLACK.b, BLACK.a); 
    SDL_RenderClear(mainScreen.getRender()); 
}