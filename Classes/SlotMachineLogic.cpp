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

SlotMachineLogic* SlotMachineLogic::create(std::vector<std::vector<int>> wheelsData)
{
  SlotMachineLogic* p = new SlotMachineLogic();
  if (p && p->initWithData(wheelsData)) {
    p->autorelease();
    return p;
  }
  CC_SAFE_DELETE(p);
    
  return nullptr;

}

bool SlotMachineLogic::initWithData(std::vector<std::vector<int>> wheelsData)
{
    if (!Node::init())
        return false;
    
    _balance = 300;
    _bet = 100;
    
    return true;
}

bool SlotMachineLogic::play()
{
    if (_balance < _bet) {
      std::cout << "Not enough balance!\n";
      return false;
  }
    
  _balance -= _bet;
    return true;
}

int SlotMachineLogic::getBalance() const
{
    return _balance;
}

void SlotMachineLogic::spinEnded(std::vector<std::vector<int>> reelsData, std::vector<int> wheelsTargetData, int bet)
 {
     _results.clear();

    for (int i = 0; i < 3; ++i) {
        std::vector<int> reelData = reelsData[i];
        _results.push_back(static_cast<Symbol>(reelData[(wheelsTargetData[i])-1]));
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

int SlotMachineLogic::increaseBet(int increaseBet)
{
    int maxBet = 1000;
    if(_bet < maxBet) {
        _bet += increaseBet;
    }
    else
    {
        _bet = 100;
    }
    return _bet;
}

void SlotMachineLogic::spinFinished(int win)
{
    bool stop = true;
}
