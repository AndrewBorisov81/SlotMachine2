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

  cocos2d::Size getCellSize() const;
    
  int getCurrentCellsCounter() const;

private:

  cocos2d::Size _cellSize { 0, 0 };
  //type of Cell(
  int _cellNumberData;
  //label on the wheel
  int _cellsCounter{ -1 };
  inline static int nextId{ -1 };
    
  const std::vector<std::string> CELLS = {
      Constants::CELL1,
      Constants::CELL2,
      Constants::CELL3,
      Constants::CELL4
    };
    
    /*const std::string& getRandomCellImage();
    int getRandomIndex();*/
};

#endif // __CELL_H__
