//
//  SlotMachineFull.cpp
//  SlotMachine3
//
//  Created by Andrew Borisov on 11.12.2025.
//

#include "Reel.h"

Reel* Reel::create(const std::vector<std::vector<int>>& wheelDatas)
{
  Reel* p = new Reel();
  if (p && p->initWithData(wheelDatas)) {
    p->autorelease();
    return p;
}
  CC_SAFE_DELETE(p);
  return nullptr;
}

bool Reel::initWithData(const std::vector<std::vector<int>>& wheelDatas)
{
  if (!Node::init())
    return false;

    _wheelDatas = std::move(wheelDatas);
    return true;
}
