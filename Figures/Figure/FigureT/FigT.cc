#include "FigT.h"

FigT::FigT(){
    //we need to make the figure relative to the leading block so that when it changes, the whole figure also changes
    this->setColor(LIGHT_PURPLE);
    this->setType("T");
    this->setId(4);

    loadInitialBlocks(true);
}

int FigT::updateBlocks(){
    //We assume that the figure position is changeable beacuse we cheched it outside
    this->deleteAllBlocks();

    loadInitialBlocks(false);
    for(int i = 0; i < (this->getAngle() / 90); i++){
        rotate();
    }

    return 0;
}

void FigT::loadInitialBlocks(bool constructor){

    Block block;
    block.setBlockColor(LIGHT_PURPLE);
    block.setOutlineColor(PURPLE);

    if(constructor){
    
        //Leading block. The position is not always 0,0 (if we cast it on the upper left corner)
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
    block.setBlockX(LeadingBlockX - 1);
    block.setBlockY(LeadingBlockY);
    getBlocks().push_back(block);

    //Block 3
    block.setBlockX(LeadingBlockX + 1);
    block.setBlockY(LeadingBlockY);
    getBlocks().push_back(block);
}