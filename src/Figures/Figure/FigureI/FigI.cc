#include "FigI.h"

FigI::FigI(){

    setId(3);
    setFigureColor(LIGHT_CYAN);

    //Constructor
    loadInitialBlocks(true);

    for(int i = 0; i < (int) getBlocks().size(); i++){
        getBlocks()[i].setBlockTexture(IMG_LoadTexture(mainScreen.getRender(), "src/Media/Textures/I-block.png"));
    }
}


int FigI::updateBlocks(){

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

bool FigI::loadInitialBlocks(bool constructor){

    Block block;
    block.setInlineColor(LIGHT_CYAN);
    block.setOutlineColor(CYAN);

    if(constructor){
        
        block.setBlockX(4);
        block.setBlockY(2);
        getBlocks().push_back(block);
    }

    int LeadingBlockX = getBlocks()[getLeadingBlockPos()].getBlockX();
    int LeadingBlockY = getBlocks()[getLeadingBlockPos()].getBlockY();

    //Block 1
    block.setBlockX(LeadingBlockX);
    block.setBlockY(LeadingBlockY - 2);
    getBlocks().push_back(block);

    //Block 2
    block.setBlockX(LeadingBlockX);
    block.setBlockY(LeadingBlockY - 1);
    getBlocks().push_back(block);

    //Block 3
    block.setBlockX(LeadingBlockX);
    block.setBlockY(LeadingBlockY + 1);
    getBlocks().push_back(block);


    if(getHasTexture()){
        for(int i = 0; i < (int) getBlocks().size(); i++){
            getBlocks()[i].setBlockTexture(IMG_LoadTexture(mainScreen.getRender(), "src/Media/Textures/I-block.png"));
        }
    }
    
    return constructor;
}
