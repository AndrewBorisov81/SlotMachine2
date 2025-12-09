#ifndef __CELL_H__
#define __CELL_H__

#include "cocos2d.h"

class Cell: public cocos2d::Node
{
public:
  Cell(int numberData);

  cocos2d::Size getCellSize()const;

private:

  cocos2d::Size _cellSize { 0, 0 };
  //label on the wheel
  int _cellNumberData;
};

#endif // __CELL_H__
