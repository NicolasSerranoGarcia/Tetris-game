#include "FigZLeft.h"

FigZLeft::FigZLeft(){
    //we need to make the figure relative to the leading block so that when it changes, the whole figure also changes
    this->setFigureColor(LIGHT_RED);
    this->setId(6);


    loadInitialBlocks(true);
}

int FigZLeft::updateBlocks(){
    //We assume that the figure position is changeable beacuse we cheched it outside
    this->deleteAllBlocks();
    
    loadInitialBlocks(false);
    for(int i = 0; i < (this->getAngle() / 90); i++){
        rotate();
    }

    return 0;
}

bool FigZLeft::loadInitialBlocks(bool constructor){
    Block block;
    block.setInlineColor(LIGHT_RED);
    block.setOutlineColor(RED);

    if(constructor){        
        //Leading block. The position is not always 0,0 (if we cast it on the upper left corner)
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