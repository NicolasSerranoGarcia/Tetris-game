#include "FigL.h"

FigL::FigL(){
    
    setId(0);
    setFigureColor(LIGHT_ORANGE);

    //Constructor
    loadInitialBlocks(true);

    for(int i = 0; i < (int) getBlocks().size(); i++){
        getBlocks()[i].setBlockTexture(IMG_LoadTexture(mainScreen.getRender(), "src/Media/Textures/L-block.png"));
    }
}

 
int FigL::updateBlocks(){

    //Delete
    deleteAllBlocks();

    //Create
    loadInitialBlocks(false);

    //Rotate
    for(int i = 0; i < getAngle() / 90; i++){
        rotate();
    }

    return 0;
}

bool FigL::loadInitialBlocks(bool constructor){

    Block block;
    block.setInlineColor(LIGHT_ORANGE);
    block.setOutlineColor(ORANGE);

    if(constructor){
        
        block.setBlockX(4);
        block.setBlockY(1);
        getBlocks().push_back(block);
    }

    int LeadingBlockX = getBlocks()[getLeadingBlockPos()].getBlockX();
    int LeadingBlockY = getBlocks()[getLeadingBlockPos()].getBlockY();

    //Block 1
    block.setBlockX(LeadingBlockX);
    block.setBlockY(LeadingBlockY - 1);
    getBlocks().push_back(block);

    //Block 2
    block.setBlockX(LeadingBlockX);
    block.setBlockY(LeadingBlockY + 1);
    getBlocks().push_back(block);

    //Block 3
    block.setBlockX(LeadingBlockX + 1);
    block.setBlockY(LeadingBlockY + 1);
    getBlocks().push_back(block);

    if(getHasTexture()){
        for(int i = 0; i < (int) getBlocks().size(); i++){
            getBlocks()[i].setBlockTexture(IMG_LoadTexture(mainScreen.getRender(), "src/Media/Textures/L-block.png"));
        }
    }

    return constructor;
}