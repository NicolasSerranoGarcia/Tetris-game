#include "FigO.h"

FigO::FigO(){

    this->setId(2);
    this->setFigureColor(LIGHT_YELLOW);

    //Constructor
    loadInitialBlocks(true);
}


int FigO::updateBlocks(){

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

bool FigO::loadInitialBlocks(bool constructor){
        
    Block block;
    block.setInlineColor(LIGHT_YELLOW);
    block.setOutlineColor(YELLOW);

    
    if(constructor){
        
        block.setBlockX(4);
        block.setBlockY(0);
        getBlocks().push_back(block);
    }

    int LeadingBlockX = getBlocks()[getLeadingBlockPos()].getBlockX();
    int LeadingBlockY = getBlocks()[getLeadingBlockPos()].getBlockY();
    
    //Block 1
    block.setBlockX(LeadingBlockX);
    block.setBlockY(LeadingBlockY + 1);
    getBlocks().push_back(block);

    //Block 2
    block.setBlockX(LeadingBlockX + 1);
    block.setBlockY(LeadingBlockY);
    getBlocks().push_back(block);

    //Block 3
    block.setBlockX(LeadingBlockX + 1);
    block.setBlockY(LeadingBlockY + 1);
    getBlocks().push_back(block);

    return constructor;
}