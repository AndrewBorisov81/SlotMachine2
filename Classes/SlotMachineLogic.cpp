//
//  SlotMachineLogic.cpp
//  SlotMachine3
//
//  Created by Andrew Borisov on 20.12.2025.
//

#include "SlotMachineLogic.h"

#include <iostream>

SlotMachineLogic::SlotMachineLogic():
   _balance(100), _bet(10)
{
    
}

void SlotMachineLogic::play()
{
  if (_balance < _bet) {
    std::cout << "Not enough balance!\n";
    return;
  }
    
  _balance -= _bet;
}

int SlotMachineLogic::getBalance() const
{
    
}

void SlotMachineLogic::checkWin(const std::vector<int>& reels)
{
    // example: simple 3-match
    if (reels.size() < 3)
        return;

    if (reels[0] == reels[1]) {
        
    } else if (reels[0] == reels[1] && reels[1] == reels[2])
    {
        _balance += _bet * 5; // win
    }
}
