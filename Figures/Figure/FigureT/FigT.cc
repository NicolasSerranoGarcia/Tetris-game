#include "FigT.h"

FigT::FigT(){
    //we need to make the figure relative to the leading block so that when it changes, the whole figure also changes
    this->setColor(LIGHT_PURPLE);
    this->setType("T");



    Block block;
    block.setBlockColor(LIGHT_PURPLE);
    block.setOutlineColor(PURPLE);
    block.setPlaced(true);
    
    //Leading block. The position is not always 0,0 (if we cast it on the upper left corner)
    block.setBlockX(1);
    block.setBlockY(1);
    getBlocks().push_back(block);
    
    int LeadingBlockX = getBlocks()[getLeadingBlockPos()].getBlockX();
    int LeadingBlockY = getBlocks()[getLeadingBlockPos()].getBlockY();
    


    //Alter the position of the block consecutively and save each time to get
    //the whole figure

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

int FigT::updateBlocks(){
    //We assume that the figure position is changeable beacuse we cheched it outside
    this->deleteAllBlocks();

    Block block;
    block.setBlockColor(LIGHT_PURPLE);
    block.setOutlineColor(PURPLE);

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

    return 0;
}