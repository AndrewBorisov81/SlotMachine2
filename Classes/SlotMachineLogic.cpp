//
//  SlotMachineLogic.cpp
//  SlotMachine3
//
//  Created by Andrew Borisov on 20.12.2025.
//

#include "SlotMachineLogic.h"
#include "SlotMachine.h"

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
    return _balance;
}

void SlotMachineLogic::spin(int bet)
 {
     _results.clear();

    for (int i = 0; i < 3; i++) {
        //_results.push_back(static_cast<Symbol>(_reels[i]->spin()));
    }

    return _results;
 }

int SlotMachineLogic::calculateWin(int bet)
{
    // example: simple 3-match
    if (_results.size() < 3)
        return;

    if (_results[0] == _results[1]) {
        _balance += _bet * 10;
    } else if (_results[0] == _results[1] && _results[1] == _results[2])
    {
        _balance += _bet * 5; // win
    }
}
