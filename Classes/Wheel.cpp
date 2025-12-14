#include "Wheel.h"
#include "Cell.h"
//#include "SimpleAudioEngine.h"

#include <vector>

USING_NS_CC;

Wheel::Wheel(std::vector<int> boxData): _boxData(boxData)
{
  createCells();
}

void Wheel::createCells()
{
  int countFirstCells = 4;
  //create cells
  Cell* cell = new Cell(_boxData[0]);
  this->addChild(cell);

  increaseIndexElementData();

  Size cellSize = cell->getCellSize();
  _cellSize = cellSize;

  Vec2 posFirstCell = Vec2(0, 0);
  Vec2 posEndCell = Vec2(0, countFirstCells * cellSize.height);

  _posFirstCell = posFirstCell;
  _posLastCell = posEndCell;

  Vec2 cellPos(posFirstCell.x, posFirstCell.y);

  cell->setPosition(cellPos);

  _cellsBox.push_back(cell);

  //create cells
  for (int i = 1; i < countFirstCells; i++)
  {
    Cell* cell = new Cell(_boxData[i]);
    this->addChild(cell);

    increaseIndexElementData();

    Vec2 cellPos(0, posFirstCell.y + i * cellSize.height);
    cell->setPosition(cellPos);

    _cellsBox.push_back(cell);
  }
}

const Cell* Wheel::addCell()
{
  _indexLastCellInWheel++;
  //create cells
  Cell* cell = new Cell(_boxData[_indexLastElementInBoxData]);
  this->addChild(cell);
  _cellsBox.push_back(cell);
  increaseIndexElementData();

  Vec2 cellPos(0, (_indexLastCellInWheel - 1) * _cellSize.height);
  cell->setPosition(cellPos);
  return cell;
}

void Wheel::deleteCell()
{
  Cell * toDeleteCell = _cellsBox[0];
  this->removeChild(toDeleteCell);
  _cellsBox.erase(_cellsBox.begin());
  _indexFirstCellInWheel++;
}

void Wheel::increaseIndexElementData()
{
  if (_indexLastElementInBoxData < (_boxData.size() - 1))
  {
    _indexLastElementInBoxData++;
  }
  else {
    _indexLastElementInBoxData = 0;
  }
}

cocos2d::Size Wheel::getCellSize()const
{
  return _cellSize;
}

int Wheel::getIndexLastCell()const
{
  return _indexLastCellInWheel;
}

int Wheel::getIndexFirstCell()const
{
  return _indexFirstCellInWheel;
}

void  Wheel::moveCellsInitPos(float deltaPosY)
{
  for (auto it = _cellsBox.begin(); it != _cellsBox.end(); ++it)
  {
    Cell * shiftCell = *it;
    Vec2 posShiftCell = shiftCell->getPosition();
    posShiftCell.y -= deltaPosY;
    shiftCell->setPosition(posShiftCell);
  }

  _indexLastCellInWheel = 4;
  _indexFirstCellInWheel = 0;
}

const std::vector<Cell*>& Wheel::getCellsBox() const
{
    return _cellsBox;
}
