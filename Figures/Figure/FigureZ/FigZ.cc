#include "FigZ.h"

FigZ::FigZ(){
    
    this->setId(6);
    this->setFigureColor(LIGHT_RED);

    //Constructor
    loadInitialBlocks(true);
}


int FigZ::updateBlocks(){

    //Delete
    deleteAllBlocks();

    //Create
    loadInitialBlocks(false);

    //Rotate
    for(int i = 0; i < getAngle() / 90; i++){
        rotateRight();
    }

    return 0;
}

bool FigZ::loadInitialBlocks(bool constructor){
    Block block;
    block.setInlineColor(LIGHT_RED);
    block.setOutlineColor(RED);

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
    block.setBlockX(LeadingBlockX - 1);
    block.setBlockY(LeadingBlockY);
    getBlocks().push_back(block);

    //Block 3
    block.setBlockX(LeadingBlockX + 1);
    block.setBlockY(LeadingBlockY + 1);
    getBlocks().push_back(block);

    return constructor;
}