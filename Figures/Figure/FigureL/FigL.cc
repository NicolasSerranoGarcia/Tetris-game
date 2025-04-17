#include "FigL.h"
#include <iostream>


FigL::FigL(){
    //we need to make the figure relative to the leading block so that when it changes, the whole figure also changes
    this->setType("L");

    loadInitialBlocks(true);
}

 
int FigL::updateBlocks(){
    //We assume that the figure position is changeable beacuse we checked it outside
    this->deleteAllBlocks();

    loadInitialBlocks(false);
        for(int i = 0; i < this->getAngle() / 90; i++){
            rotate();
        }

    return 0;
}

void FigL::loadInitialBlocks(bool constructor){

    Block block;
    block.setBlockColor(LIGHT_ORANGE);
    block.setOutlineColor(ORANGE);

    if(constructor){
        block.setPlaced(true);
    
        //Leading block. The position is not always 0,0 (if we cast it on the upper left corner)
        block.setBlockX(0);
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
}