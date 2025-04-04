#ifndef SCREEN_H
#define SCREEN_H

#include <SDL2/SDL.h>
#include <vector>

class Screen {
private:
    int width;
    int height;
    static SDL_Window* window;
    static SDL_Renderer* render;
    static std::vector<SDL_Texture*> textures;

public:
    Screen(int w, int h);
    unsigned int getWidth();
    unsigned int getHeight();
    static SDL_Window* getWindow();
    static SDL_Renderer* getRender();
    static std::vector<SDL_Texture*>* getTextures();
    void showSquare(SDL_Rect rect, SDL_Color color);
};

#endif