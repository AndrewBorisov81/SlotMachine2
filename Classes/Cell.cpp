#include "Cell.h"
#include "Constants.h"
#include <string>
//#include "SimpleAudioEngine.h"
#include "math.h"
#include <random>

USING_NS_CC;

Cell::Cell(int numberData, int cellsCounter):_cellNumberData(numberData), _cellsCounter(cellsCounter)
{
  _cellType = static_cast<CellType>(_cellNumberData);
    
  //Frame
  auto mySprite = Sprite::createWithSpriteFrameName(CELLS[_cellNumberData]);
  this->addChild(mySprite, 10);

  Size spriteSize = mySprite->getContentSize();

  _cellSize.width = spriteSize.width;
  _cellSize.height = spriteSize.height;

  //std::string s = std::to_string(_cellNumberData);
  std::string s = std::to_string(_cellsCounter);

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

int Cell::getCurrentCellsCounter() const
{
    return _cellsCounter;
}

void Cell::setCellsCounter(int cellsCounter)
{
    _cellsCounter = cellsCounter;
}

Cell::CellType Cell::getCellType() const
{
    return _cellType;
}
