#include "FigStick.h"

FigStick::FigStick(){
    //we need to make the figure relative to the leading block so that when it changes, the whole figure also changes
    this->setColor(LIGHT_CYAN);

    Block block;
    block.setBlockColor(LIGHT_CYAN);
    block.setOutlineColor(CYAN);
    block.setPlaced(true);
    
    //Leading block. The position is not always 0,0 (if we cast it on the upper left corner)
    block.setBlockX(0);
    block.setBlockY(2);
    getBlocks().push_back(block);
    
    int LeadingBlockX = getBlocks()[getLeadingBlockPos()].getBlockX();
    int LeadingBlockY = getBlocks()[getLeadingBlockPos()].getBlockY();
    


    //Alter the position of the block consecutively and save each time to get
    //the whole figure

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
}

int FigStick::updateBlocks(){

}