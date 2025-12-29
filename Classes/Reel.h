#ifndef __REEL_H__
#define __REEL_H__
//
//  SlotMachineWheels.h
//  SlotMachine3
//
//  Created by Andrew Borisov on 11.12.2025.
//
#include "cocos2d.h"

#include <functional>
#include <vector>

class SlotMachine;

class Reel: public cocos2d::Node
{
  
public:
    using SpinCallback = std::function<void(int win)>;
    
    void setOnSpinFinished(SpinCallback cb);
    
    static Reel* create(std::vector<std::vector<int>> wheelsDatas);

    bool initWithData(std::vector<std::vector<int>> wheelsDatas);
    
    void update(float) override;
    
    void startStopMachine(std::vector<int> targetCell);
    
    bool allWheelsStopped();
    bool allWheelsSpin();
    bool allWheelsBreak();
    bool allWheelsFindTarget();
    
private:
    Reel() = default;
    
    std::vector<SlotMachine*> _slotMachines;
    
    //SlotMachineLogic* _sMLogic;
    
    std::vector<std::vector<int>> _wheelDatas;
    
    SpinCallback _onSpinFinished;
};

#endif //__REEL_H__

