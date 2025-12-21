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

void SlotMachineLogic::checkWin(const std::vector<std::string>& reels)
{
  if (reels[0] == reels[1] && reels[1] == reels[2]) {
    int win = _bet * 5;
    _balance += win;
    std::cout << "🎉 JACKPOT! You win " << win << "\n";
  }
  else if (reels[0] == reels[1] ||
    reels[1] == reels[2] ||
    reels[0] == reels[2]) {
    int win = _bet * 2;
    _balance += win;
      std::cout << "🙂 Small win! You win " << win << "\n";
    }
    else {
      std::cout << "😢 You lose!\n";
  }
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
