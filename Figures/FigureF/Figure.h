#ifndef FIGURE_H
#define FIGURE_H

#include "Figures/Block/Block.h"
#include "constants/constants.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <string>


//This class serves as an abstract father class of the figures. Almost any aspect of a figure
//can be generalized in this class. This class holds methods for rotating, deleting blocks, rendering...
//IMPORTANT: There are several things that each child must implement in it's own way, like the actual
//position of the blocks (which is different for every figure). It is worth to mention that anything related
//with the building or rotating of the figure is based on the leading block. Keep it in mind when looking
//at the build process of every figure, as you may see something like leadingBlock - 1. It is important that
//the leading block is correctly updated.
class Figure{

    private:

        //The identifier of the figure. Used to distinguish
        //from different types of figures
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

        bool hasTexture = false;

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
        
        //Getter
        //
        //RETURNS:
        //a boolean representing if the figure should be rendered with a texture
        virtual bool getHasTexture();

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
        
        //Setter
        //
        //RETURNS:
        //void
        virtual void setHasTexture(bool texture);

        //MISCElLANEOUS

        //This method takes an event (the event can only be a key press)
        //and it updates the LEADING BLOCK according to the key pressed.
        //In the case of rotations, it just updates the angle of the figure.
        //Regardless of the key action pressed, the method calls updateBlocks()
        //which will update the rest of the blocks according to the event. 
        //This function just "triggers" the all of the blocks position to change 
        //by changing the leading block
        //RETURNS:
        //-1 if there were no updates in the figure
        //0 if the update was done successfully
        virtual int update(SDL_Event event);

        //This method updates the blocks after a figure event (like moving to the left).
        //Each figure has it's own updateBlocks(), so you will see the father method empty.
        //Anyways, all the methods of the figures have the same procedure. The figure blocks are 
        //deleted, then built again, then rotated. This way, it is safe to call the method even 
        //if the figure hasn't been updated in any way. This is because if no parameters of the 
        //figure have been changed, the method will construct the same figure again. See the
        //documentation for detailed info
        //
        //RETURNS:
        //Always 0
        virtual int updateBlocks();

        //This method rotates the figure, having the axis of rotation in the leading block.
        //The figure will always rotate by 90º, regardless of the angle.  
        //
        //RETURNS:
        //void
        virtual void rotate();


        //This method is a virtual method. Each child class implements it's own way of handling
        //with the figure creation. In short, what this method does is build the figure as it 
        //it had 0º of rotation, BUT it does it relative to the leading block, which is not changed.
        //This method is usually called after deleteAllBlocks(), as it is needed to update the figure
        //if there are any events, like rotating. The parameter is used as a way to know if it is the first
        //time constructing the figure. It will enable setting the position of the leading block.
        //It will normally only be true if we are calling the method from the constructor.
        //
        //RETURNS:
        //the value of the parameter
        virtual bool loadInitialBlocks(bool constructor);

        //This method deletes blocks[pos]. Keep in mind it compacts the vector
        //
        //RETURNS:
        //void
        virtual void deleteBlock(int pos);

        //This method deletes all blocks inside the vector, except for the leading block
        //
        //RETURNS:
        //void
        virtual void deleteAllBlocks();

        //This method adds a block to the end of the vector of blocks. 
        //
        //RETURNS:
        //void
        virtual void addBlock(Block block);

        //This method renders the figure by rendering all the distinct blocks. Keep in mind
        //it doesn't directly show the figure
        //
        //RETURNS:
        //void
        virtual void renderFigure();

};

#endif