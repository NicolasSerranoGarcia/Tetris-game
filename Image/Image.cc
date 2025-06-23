#include "Image.h"

Image::Image(int x, int y, int w, int h, std::string imgName, std::string imgType){
    this->x = x;
    this->y = y;
    width = w;
    height = h;

    imageType = imgType;
    imageName = imgName;

    std::string path = "Media/" + imageName + "." + imageType;
    imageTexture = IMG_LoadTexture(mainScreen.getRender(), path.c_str());
}

Image::~Image(){
    x = 0; 
    y = 0;
    width = 0;
    height = 0;

    imageType = "";
    imageName = "";

    SDL_DestroyTexture(imageTexture);
    imageTexture = nullptr;
}


int Image::getX() const{
    return x;
}

int Image::getY() const{
    return y;
}

int Image::getWidth() const{
    return width;
}

int Image::getHeight() const{
    return height;
}

std::string Image::getType() const{
    return imageType;
}

std::string Image::getName() const{
    return imageName;
}

SDL_Texture * Image::getTexture() const{
    return imageTexture;
}


void Image::setNewPhoto(std::string newName, std::string newType){
    imageName = newName;
    imageType = newType;

    x = 0;
    y = 0;

    width = 50;
    height = 50;

    std::string path = "Media/" + imageName + "." + imageType;
    imageTexture = IMG_LoadTexture(mainScreen.getRender(), path.c_str());
}

void Image::setHeight(int height){
    this->height = height;
}

void Image::setWidth(int width){
    this->width = width;
}

void Image::setX(int x){
    this->x = x;
}

void Image::setY(int y){
    this->y = y;
}


void Image::CopyToRender() const{
    SDL_Rect ImageRect = {getX(), getY(), getWidth(), getHeight()};
    SDL_RenderCopy(mainScreen.getRender(), getTexture(), NULL, &ImageRect);
}

void Image::setAsBackground() const{
    SDL_Rect ImageRect = {0, 0, mainScreen.getWidth(), mainScreen.getHeight()};
    SDL_RenderCopy(mainScreen.getRender(), getTexture(), NULL, &ImageRect);
}