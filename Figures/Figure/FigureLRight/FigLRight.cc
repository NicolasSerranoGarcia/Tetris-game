#include "FigLRight.h"

FigLRight::FigLRight(){
    this->setId(1);
    this->setFigureColor(LIGHT_BLUE);

    //Constructor
    loadInitialBlocks(true);
    
}

int FigLRight::updateBlocks(){
    
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

bool FigLRight::loadInitialBlocks(bool constructor){

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

    return constructor;
}