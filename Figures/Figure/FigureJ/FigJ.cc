#include "FigJ.h"

FigJ::FigJ(){
    
    this->setId(1);
    this->setFigureColor(LIGHT_BLUE);

    //Constructor
    loadInitialBlocks(true); 

    for(int i = 0; i < (int) getBlocks().size(); i++){
        getBlocks()[i].setBlockTexture(IMG_LoadTexture(mainScreen.getRender(), "Media/Textures/J-block.png"));
    }
}


int FigJ::updateBlocks(){
    
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

bool FigJ::loadInitialBlocks(bool constructor){

    Block block;
    block.setInlineColor(LIGHT_BLUE);
    block.setOutlineColor(BLUE);

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
    block.setBlockX(LeadingBlockX - 1);
    block.setBlockY(LeadingBlockY + 1);
    getBlocks().push_back(block);

    if(getHasTexture()){
        for(int i = 0; i < (int) getBlocks().size(); i++){
            getBlocks()[i].setBlockTexture(IMG_LoadTexture(mainScreen.getRender(), "Media/Textures/J-block.png"));
        }
    }

    return constructor;
}