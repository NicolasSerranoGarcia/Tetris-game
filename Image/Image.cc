#include "Image.h"

Image::Image(int x, int y, int w, int h, std::string imgName){
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->imageName = imgName;
    std::string path = "IMG/" + getName() + ".png";
    this->IMGTexture = IMG_LoadTexture(mainScreen.getRender(), path.c_str());
}


int Image::getW() const{
    return this->w;
}

int Image::getH() const{
    return this->h;
}

int Image::getX() const{
    return this->x;
}

int Image::getY() const{
    return this->y;
}

SDL_Texture * Image::getTexture() const{
    return this->IMGTexture;
}

std::string Image::getName() const{
    return this->imageName;
}

//only loads to render. TO show the image, do Screen.Update();
void Image::CopyToRender() const{
    //maybe add some other method to set an image as a backogrund directly
    SDL_Rect IMGrect = {getX(), getY(), getW(), getH()};
    SDL_RenderCopy(mainScreen.getRender(), getTexture(), NULL, &IMGrect);
}