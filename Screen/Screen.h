#ifndef SCREEN_H
#define SCREEN_H

#include <SDL2/SDL.h>
#include <vector>
#include <string>

class Screen {
private:
    int width;
    int height;
    std::string title;
    static SDL_Window* window;
    static SDL_Renderer* render;
    static std::vector<SDL_Texture*> textures;

public:
    Screen(int w, int h, const char * title);
    unsigned int getWidth();
    unsigned int getHeight();
    static SDL_Window* getWindow();
    static SDL_Renderer* getRender();
    static std::vector<SDL_Texture*>* getTextures();
    std::string getTitle();
    void showSquare(SDL_Rect rect, SDL_Color color);
    void Update();
    void clear(SDL_Color color);
};

#endif