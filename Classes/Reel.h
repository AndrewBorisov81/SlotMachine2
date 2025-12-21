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
    
    static Reel* create(const std::vector<int>& wheelDatas);

    virtual bool initWithData(const std::vector<int>& wheelDatas);
private:
    Reel() = default;
    
    std::vector<SlotMachine*> _slotMachines;
    
    std::vector<int> _wheelDatas;
};

#endif //__REEL_H__


