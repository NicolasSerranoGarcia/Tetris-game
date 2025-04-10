#ifndef IMAGE_H
#define IMAGE_H

#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <string>
#include "Screen/Screen.h"
#include "constants/constants.h"


class Image{
    private:
        SDL_Texture* IMGTexture;
        std::string imageName;
        int w;
        int h;
        int x;
        int y;
        std::string imageType;
    public:
        Image(int x, int y, int w, int h, std::string imgName, std::string imageType);
        int getW() const;
        int getH() const;
        int getX() const;
        int getY() const;
        std::string getType() const;

        SDL_Texture * getTexture() const;
        std::string getName() const;
        void CopyToRender() const;


};


#endif