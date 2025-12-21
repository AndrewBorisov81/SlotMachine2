//
//  SlotMachineLogic.h
//  SlotMachine3
//
//  Created by Andrew Borisov on 20.12.2025.
//

#ifndef __SLOT_MACHINE_LOGIC_H__
#define __SLOT_MACHINE_LOGIC_H__

#include "cocos2d.h"

class SlotMachineLogic: public cocos2d::Node
{
public:
    SlotMachineLogic();
    
    void play();
    int getBalance() const;
    
private:
   int _balance;
   int _bet;
    
   void checkWin(const std::vector<std::string>& reels);
};

#endif //__SLOT_MACHINE_LOGIC_H__
