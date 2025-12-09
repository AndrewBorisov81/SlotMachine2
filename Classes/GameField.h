#ifndef __GAME_FIELD_H__
#define __GAME_FIELD_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class GameField: public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameField);
};

#endif // __GAME_FIELD_H__
