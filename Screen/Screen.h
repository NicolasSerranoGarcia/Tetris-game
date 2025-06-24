#ifndef SCREEN_H
#define SCREEN_H

#include <SDL2/SDL.h>
#include <vector>
#include <string>

//This class holds the necessary objects to start a window and draw things to it.
//There's currently one global instance of this class, called mainScreen. The
//normal functioning of the class is to use the render attribute, which is static,
//to render whatever must be render at the moment. You will normally see this
//put to practice when I do something like SDL_RenderPresent(mainScreen.getRender());
//which will show all the rendering process made before
class Screen {

    private:

        //The width of the screen
        int width;

        //The height of the screen
        int height;

        //The title that appears on the navbar of the screen
        std::string title;

        //The window associated with the screen of the game
        static SDL_Window* window;

        //The render where all the scenes will be shown accordingly. Only one render
        //is used on the program. Luckily SDL renders are not shown directly on the screen,
        //so this render will be loaded each time the game refreshes with what needs to be 
        //shown and the cleared
        static SDL_Renderer* render;

        //Textures used on the scenes. Currently empty
        static std::vector<SDL_Texture*> textures;

    public:

        //CONSTRUCTORS/DESTRUCTOR

        //Constructor. The start of the program should be the only place where a screen is opened. All the operations will be performed on this screen.
        Screen(int w, int h, const char * title);
    
        //Destructor
        ~Screen();


        //GETTERS

        //Getter
        //
        //RETURNS:
        //An integer representing the width in pixels (px) of the screen
        int getWidth() const;

        //Getter
        //
        //RETURNS:
        //An integer representing the height in pixels (px) of the screen
        int getHeight() const;

        //Getter
        //
        //RETURNS:
        //A string representing the title of the screen
        std::string getTitle() const;

        //Getter
        //
        //RETURNS:
        //A pointer to the SDL_Window of the screen
        static SDL_Window* getWindow();

        //Getter
        //
        //RETURNS:
        //A pointer to the SDL_Renderer of the screen
        static SDL_Renderer* getRender();

        //Getter
        //
        //RETURNS:
        //A pointer to the vector of textures of the screen. The elements 
        //of the vector are also pointers to SDL_Texture instances.
        //Currently no use of it
        static std::vector<SDL_Texture*> getTextures();


        //SETTERS

        //Setter
        //
        //RETURNS:
        //void
        void setWidth(int w);

        //Setter
        //
        //RETURNS:
        //void
        void setHeight(int h);

        //Setter
        //
        //RETURNS:
        //void
        void setTitle(int title);


        //MISCELLANEOUS

        //Method that receives a rectangle and a color; renders the rectangle (the interior too) and shows it.
        //This method calls SDL_RenderPresent
        //
        //RETURNS:
        //void 
        void showSquare(SDL_Rect rect, SDL_Color color) const;

        //Method that receives a color and clears the screen. Clear means that
        //the next frame will just be an empty frame with the background color
        //that was chosen, ready to be filled with objects again.
        //
        //RETURNS: 
        //void
        void clear(SDL_Color color);

};

#endif