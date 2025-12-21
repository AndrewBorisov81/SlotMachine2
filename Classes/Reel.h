#ifndef __REEL_H__
#define __REEL_H__
//
//  SlotMachineWheels.h
//  SlotMachine3
//
//  Created by Andrew Borisov on 11.12.2025.
//
#include "cocos2d.h"

#include <vector>

class SlotMachine;

class Reel: public cocos2d::Node
{
public:
    Reel(const std::vector<int>& wheelDatas);
private:
    std::vector<SlotMachine*> _slotMachines;
};

#endif //__REEL_H__



