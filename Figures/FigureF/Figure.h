#ifndef FIGURE_H
#define FIGURE_H

#include "Figures/Block/Block.h"
#include "constants/constants.h"

#include <SDL2/SDL.h>
#include <vector>
#include <string>


//This class serves as an abstract father class of the figures. Almost any aspect of a figure
//can be generalized in this class. This class holds methods for rotating, deleting blocks, rendering...
//IMPORTANT: There are several things that each child must implement in it's own way, like the actual
//position of the blocks (which is diferent for every figure). It is worth to mention that anything related
//with the building or rotating of the figure is based on the leading block. Keep it in mind when looking
//at the build process of every figure, as you may see something like leadingBlock - 1. It is important that
//the leading block is correctly updated.
class Figure{

    private:

        //The identifier of the figure. Used to distinguish
        //from diferent types of figures
        int id;

        //The container for all the blocks of the figure
        std::vector <Block>blocks;

        //The current angle of the figure. 0º <= angle < 360º
        //It updates automatically with events
        int angle;

        //The general color of the figure. It coincides with
        //the inline color of the block
        SDL_Color figureColor;
        
        //The position of the leading block inside the vector
        //of blocks. DO NOT CHANGE
        int leadingBlockPos;

    public:

        //CONSTRUCTORS/DESTRUCTOR

        //Constructor. Note that this is the general purpose
        //constructor, each child will have it's own.
        Figure();

        //Destructor
        virtual ~Figure();


        //GETTERS

        //Getter
        //
        //RETURNS:
        //An integer representing the id of the figure
        virtual int getId();

        //Getter
        //
        //RETURNS:
        //The vector of blocks of the figure
        virtual std::vector <Block> &getBlocks();

        //Getter
        //
        //RETURNS:
        //An integer representing the angle of the figure
        virtual int getAngle();

        //Getter
        //
        //RETURNS:
        //An SDL_Color instance representing the color of the figure
        virtual SDL_Color getFigureColor();

        //Getter
        //
        //RETURNS:
        //An integer representing the leading block position inside the
        //vector of blocks
        virtual int getLeadingBlockPos();
        

        //SETTERS

        //Setter
        //
        //RETURNS:
        //void
        virtual void setId(int id);
        
        //Setter
        //
        //RETURNS:
        //void
        virtual void setAngle(int angle);

        //Setter
        //Also sets all the blocks inline color to
        //the parsed variable
        //
        //RETURNS:
        //void
        virtual void setFigureColor(SDL_Color color);

        //Setter
        //DO NOT USE 
        //
        //RETURNS:
        //void
        virtual void setLeadingBlockPos(int pos);
        

        //MISCELANEOUS

        //This method takes an event (the event can only be a key press)
        //and it updates the LEADING BLOCK according to the key pressed.
        //In the case of rotations, it just updates the angle of the figure.
        //Regardless of the key action pressed, the method calls updateBlocks()
        //which will update the rest of the blocks according to the event. 
        //This function just "triggers" the all of the blocks position to change 
        //by changing the leading block
        //RETURNS:
        //-1 if there were no updates in the figure
        //0 if the update was done succesfully
        virtual int update(SDL_Event event);
        virtual int updateBlocks();
        virtual void rotate();
        virtual void loadInitialBlocks(bool constructor);
        virtual void deleteBlock(int pos);
        virtual void addBlock(Block block);
        virtual void deleteAllBlocks();


        virtual void renderFigure();
};

#endif