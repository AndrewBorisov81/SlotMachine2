//
//  SlotMachineLogic.h
//  SlotMachine3
//
//  Created by Andrew Borisov on 20.12.2025.
//

#ifndef __SLOT_MACHINE_LOGIC_H__
#define __SLOT_MACHINE_LOGIC_H__

#include "cocos2d.h"

enum class Symbol
{
    HORSESHOE = 0,
    HEART,
    CHERRY,
    LEMON
};

struct PayTable
{
    static int getMultiplier(Symbol s)
    {
        switch (s)
        {
            case Symbol::CHERRY: return 5;
            case Symbol::LEMON:  return 3;
            case Symbol::HORSESHOE:  return 20;
            case Symbol::HEART:    return 10;
            default: return 0;
        }
    }
};

class SlotMachineLogic: public cocos2d::Node
{
    
public:
    SlotMachineLogic();
    
    void play();
    int getBalance() const;
    
private:
   int _balance;
   int _bet;
    
   void checkWin(const std::vector<int>& reels);
};

#endif //__SLOT_MACHINE_LOGIC_H__
