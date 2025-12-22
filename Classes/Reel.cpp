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
        //SlotMachine* slotMachine = new SlotMachine(wheelDatas[i]);
        auto slotMachine = SlotMachine::create(_wheelDatas[i]);
        slotMachine->setPosition(Vec2(kShiftX[i] * frameSize.width, 0.5 * frameSize.height));
        frameSprite->addChild(slotMachine, 30);
        _slotMachines.push_back(slotMachine);
    }
    
    return true;
}

