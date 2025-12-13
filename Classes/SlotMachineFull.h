#ifndef __SLOT_MACHINE_FULL_H__
#define __SLOT_MACHINE_FULL_H__
//
//  SlotMachineWheels.h
//  SlotMachine3
//
//  Created by Andrew Borisov on 11.12.2025.
//
#include "cocos2d.h"

#include <vector>

class SlotMachine;

class SlotMachineFull: public cocos2d::Node
{
public:
    SlotMachineFull(const std::vector<std::vector<int>>& wheelDatas, std::vector<int> targetCells);
private:
    std::vector<SlotMachine*> _slotMachines;
};

#endif //__SLOT_MACHINE_FULL_H__



