//
//  SlotMachineLogic.cpp
//  SlotMachine3
//
//  Created by Andrew Borisov on 20.12.2025.
//

#include "SlotMachineLogic.h"
#include "SlotMachine.h"

#include <iostream>
#include <vector>

SlotMachineLogic::SlotMachineLogic(std::vector<std::vector<int>> wheelsData, std::vector<int> targetCells):
  _balance{100},
  _bet{10},
  _targetCells{std::move(targetCells)}
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

void SlotMachineLogic::spin(std::vector<int> wheelsTargetData, int bet)
 {
     _results.clear();

    for (int i = 0; i < 3; i++) {
        //_results.push_back(static_cast<Symbol>(_reels[i]));
    }

    return _results;
 }

int SlotMachineLogic::calculateWin(int bet)
{
    if (_results.size() < 3)
        return;

    if (_results[0] == _results[1]) {
        _balance += _bet * PayTable::getMultiplier(_results[0]);
        // All 3 symbols match
    } else if (_results[0] == _results[1] && _results[1] == _results[2])
    {
        _balance += _bet * PayTable::getMultiplier(_results[0]); // win
    }
}
