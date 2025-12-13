#include "Cell.h"
#include "Constants.h"
#include <string>
//#include "SimpleAudioEngine.h"
#include "math.h"
#include <random>

USING_NS_CC;

int Cell::getRandomIndex() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dist(0, 3); // 0..3
    return dist(gen);
}

const std::string& Cell::getRandomCellImage() {
    return CELLS[getRandomIndex()];
}

Cell::Cell(int numberData):_cellNumberData(numberData)
{
  if(_cellCounter < 50)
  {
      _cellCounter++;
  } else
  {
    _cellCounter = 0;
  }

  //Frame
  //auto mySprite = Sprite::createWithSpriteFrameName(getRandomCellImage());
    auto mySprite = Sprite::createWithSpriteFrameName(CELLS[_cellNumberData]);
  this->addChild(mySprite, 10);

  Size spriteSize = mySprite->getContentSize();

  _cellSize.width = spriteSize.width;
  _cellSize.height = spriteSize.height;

  //std::string s = std::to_string(_cellNumberData);
  std::string s = std::to_string(_cellCounter);

  //Text number label
  Label* cellNumberLabel = Label::createWithTTF(s, "fonts/arial.ttf", 35);
  cellNumberLabel->setColor(Color3B(0, 0, 0));
  //add the label as a child to this layer
  this->addChild(cellNumberLabel, 20);
}

cocos2d::Size Cell::getCellSize()const
{
  return _cellSize;
}
