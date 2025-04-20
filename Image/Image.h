#ifndef IMAGE_H
#define IMAGE_H

#include "Screen/Screen.h"
#include "constants/constants.h"

#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <string>

//This class implements an easy and fast way to use images inside the screen.
//You can load images inside buttons or directly in the screen. It is necessary
//to initialize the image library to use this class. You can do that by calling
//IMG_Init() and passing the required arguments. 
class Image{

    private:
    
        //The X position in pixels where the image is located in the screen
        int x;
    
        //The Y position in pixels where the image is located in the screen
        int y;

        //The width of the image
        int width;

        //The height of the image
        int height;
        
        //What comes before .png or .jpg
        std::string imageName;
        
        //The format (.jpg or .png in this project)
        std::string imageType;
        
        //The texture of the image. It acts as
        SDL_Texture* imageTexture;

    public:

        //CONSTRUCTORS/DESTRUCTOR

        //Constructor
        Image(int x, int y, int w, int h, std::string imgName, std::string imageType);

        //Destructor
        ~Image();


        //GETTERS

        //Getter
        //
        //RETURNS:
        //An integer representing the X position in pixels of the image
        int getX() const;

        //Getter
        //
        //RETURNS:
        //An integer representing the Y position in pixels of the image
        int getY() const;

        //Getter
        //
        //RETURNS:
        //An integer representing the Width in pixels of the image
        int getWidth() const;

        //Getter
        //
        //RETURNS:
        //An integer representing the Height in pixels of the image
        int getHeight() const;

        //Getter
        //
        //RETURNS:
        //A string representing the file type of the iamge (.png or .jpg)
        std::string getType() const;
        
        //Getter
        //
        //RETURNS:
        //A string representing the name that precedes the file type (NAME.png)
        std::string getName() const;
        
        //Getter
        //
        //RETURNS:
        //A pointer to the texture that holds the image
        SDL_Texture * getTexture() const;


        //SETTERS
        
        //Setter
        //Loads a new image texture with a standard dimension of 50x50 px
        //To change x,y,w,h properties use setters. Keep in mind any rendering
        //performed after calling this method will place the image on (0,0)
        //
        //RETURNS:
        //void
        void setNewPhoto(std::string newName, std::string newType);

        //Setter
        //
        //RETURNS:
        //void
        void setHeight(int height);

        //Setter
        //
        //RETURNS:
        //void
        void setWidth(int width);

        //Setter
        //
        //RETURNS:
        //void
        void setX(int x);

        //Setter
        //
        //RETURNS:
        //void
        void setY(int y);

        
        //MISCELANEOUS

        //This method renders the image to the screen. Keep
        //in mind this deosn't show the image, you will need
        //to do Screen::update() or directly call mainScreen.update()
        //
        //RETURNS:
        //void
        void CopyToRender() const;

        //This method does the same as CopyToRender() but sets the width
        //and the height of the image to the ones of the mainScreen. Keep
        //in mind this deosn't show the image, you will need
        //to do Screen::update() or directly call mainScreen.update()
        //
        //RETURNS:
        //void
        void setAsBackground() const;
};


#endif