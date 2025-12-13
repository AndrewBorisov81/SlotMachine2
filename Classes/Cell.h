#ifndef __CELL_H__
#define __CELL_H__

#include "cocos2d.h"

#include "Constants.h"

#include <vector>
#include <string>

class Cell: public cocos2d::Node
{
    
    enum class CellType {
        
    };
    
public:
  Cell(int numberData);

  cocos2d::Size getCellSize()const;

private:

  cocos2d::Size _cellSize { 0, 0 };
  //label on the wheel
  int _cellNumberData;
  inline static int _cellCounter{ -1 };
    
  const std::vector<std::string> CELLS = {
      Constants::CELL1,
      Constants::CELL2,
      Constants::CELL3,
      Constants::CELL4
    };
    
    const std::string& getRandomCellImage();
    int getRandomIndex();
};

#endif // __CELL_H__
