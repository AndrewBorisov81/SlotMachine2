#ifndef __GAME_FIELD_H__
#define __GAME_FIELD_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class SlotMachine;
class SlotMachineLogic;
class Reel;

class GameField: public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameField);
    
private:
    cocos2d::Label* _betCountLabel;
    Reel* _reel;
    SlotMachineLogic* _sMLogic;
    int _currentBet;
    
};

#endif // __GAME_FIELD_H__
