//
//  SlotMachineFull.cpp
//  SlotMachine3
//
//  Created by Andrew Borisov on 11.12.2025.
//

#include "Reel.h"
#include "SlotMachine.h"
#include "Constants.h"

USING_NS_CC;

Reel* Reel::create(std::vector<std::vector<int>> wheelDatas)
{
  Reel* p = new Reel();
  if (p && p->initWithData(wheelDatas)) {
    p->autorelease();
    return p;
}
  CC_SAFE_DELETE(p);
  return nullptr;
}

bool Reel::initWithData(std::vector<std::vector<int>> wheelDatas)
{
  if (!Node::init())
    return false;

    _wheelDatas = std::move(wheelDatas);
    
    //Frame Slot Machine
    auto frameSprite = Sprite::create(Constants::FRAME_WHEEL);
    //frameSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(frameSprite, 40);
      
    Size frameSize = frameSprite->getContentSize();
    
    std::vector<double> kShiftX = {0.19, 0.38, 0.57};
    
    for (int i=0; i < _wheelDatas.size(); i++)
    {
        //slot machine
        auto slotMachine = SlotMachine::create(_wheelDatas[i]);
        slotMachine->setPosition(Vec2(kShiftX[i] * frameSize.width, 0.5 * frameSize.height));
        frameSprite->addChild(slotMachine, 30);
        _slotMachines.push_back(slotMachine);
    }
    
    return true;
}


void Reel::startStopMachine(std::vector<int> targetCell)
{
    std::vector<float> delay = { 0, 0.2f, 0.4f };
    
    if(allWillsSpin() == true || allWillsStopped() == true)
    {
        for(int i=0; i < _slotMachines.size(); i++) {
            auto slotMachine = _slotMachines[i];
            
            if(slotMachine->getState() == SlotMachine::State::STOP) {
                this->runAction(Sequence::create
                                 (DelayTime::create(delay[i]),   // delay in seconds
                                  CallFunc::create([this, i, slotMachine, targetCell]()
                                  {
                                    slotMachine->startStopMachine(targetCell[i]);
                                  }),
                                  nullptr
                                 )
                             );
            } else {
                slotMachine->startStopMachine(targetCell[i]);
            }
        }
    }
}

bool Reel::allWillsStopped() {
    for(auto slotMachine: _slotMachines)
    {
        if(slotMachine->getState() != SlotMachine::State::STOP)
        {
            return false;
        }
    }
    return true;
}

bool Reel::allWillsSpin() {
    for(auto slotMachine: _slotMachines)
    {
        if(slotMachine->getState() != SlotMachine::State::SPIN)
        {
            return false;
        }
    }
    return true;
}

