#ifndef __WHEEL_H__
#define __WHEEL_H__

#include "cocos2d.h"

class Cell;

class Wheel: public cocos2d::Node
{
  public:
    Wheel(std::vector<int> boxData);

    void increaseIndexElementData();

    void createCells();
    void addCell();
    void deleteCell();

    cocos2d::Size getCellSize()const;

    int getIndexLastCell()const;
    int getIndexFirstCell()const;

    void moveCellsInitPos(float deltaPosY);
    
    const std::vector<Cell*>& getCellsBox() const;

  private:
    std::vector<int> _boxData;

    cocos2d::Size _cellSize { 0, 0 };

    int _indexLastCellInWheel { 4 };
    int _indexFirstCellInWheel{ 0 };

    std::vector<Cell*> _cellsBox;
    std::vector<Cell*> _cellsBoxToDelete;

    int _indexLastElementInBoxData { 0 };

    cocos2d::Vec2 _posLastCell {0, 0};
    cocos2d::Vec2 _posFirstCell{ 0, 0 };

    bool _fAddCell { false };
};

#endif // __WHEEL_H_
