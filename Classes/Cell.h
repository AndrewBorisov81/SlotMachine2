#ifndef __CELL_H__
#define __CELL_H__

#include "cocos2d.h"

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
    
  const std::vector<std::string> CELLS = {
        "IconSLM1.png",
        "IconSLM2.png",
        "IconSLM3.png",
        "IconSLM4.png"
    };
    
    const std::string& getRandomCellImage();
    int getRandomIndex();
};

#endif // __CELL_H__
