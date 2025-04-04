#include <SDL2/SDL.h>
#include <vector>

class Screen{
    private:
        unsigned int width;
        unsigned int height;
        static SDL_Window *window;
        static SDL_Renderer *render;
        static std::vector <SDL_Texture> * textures; //it is more efficient to just have a pointer to the array rather than the whole array

    public:
        Screen(int w, int h);
        unsigned int getWidth();
        unsigned int getHeight();
        static SDL_Window * getWindow();
        static SDL_Renderer * getRender();
        static std::vector <SDL_Texture> * getTextures();
        void showSquare(SDL_Rect rect, SDL_Color color); //shows the parsed square in screen



};