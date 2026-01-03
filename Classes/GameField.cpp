#include "GameField.h"
#include "SlotMachine.h"
#include "SlotMachineLogic.h"
//#include "SimpleAudioEngine.h"
#include "Constants.h"
#include "Reel.h"
#include <vector>

USING_NS_CC;
using namespace cocos2d::ui;

Scene* GameField::createScene()
{
  //'scene' is an autorelease object
  auto scene = Scene::create();

  auto layer = GameField::create();

  scene->addChild(layer);

  return scene;
}

// on "init" you need to initialize your instance
bool GameField::init()
{
  //////////////////////////////
  // 1. super init first
  if (!Layer::init())
  {
    return false;
  }

  auto visibleSize = Director::getInstance()->getVisibleSize();
  Vec2 origin = Director::getInstance()->getVisibleOrigin();

  //load the Sprite Sheet
  auto spritecache = SpriteFrameCache::getInstance();
    spritecache->addSpriteFramesWithFile(Constants::ICONS_PLIST);

  //Bg
  LayerColor * bgColor = LayerColor::create(Color4B(80, 122, 220, 255));
  this->addChild(bgColor, -30);
    
  std::vector<int> jsonData1 = {
    0, 0, 3, 3, 2, 0, 1, 3, 3, 2,
    2, 1, 0, 3, 0, 2, 1, 1, 3, 2
  };
  
  std::vector<int> jsonData2 = {
    2, 1, 3, 0, 2, 3, 2, 3, 0, 0,
    0, 0, 2, 3, 1, 3, 1, 0, 3, 1
  };
    
  std::vector<int> jsonData3 = {
    2, 3, 1, 1, 3, 0, 2, 1, 2, 2,
    3, 2, 3, 1, 2, 2, 0, 3, 3, 0
  };
    
  // When to stop wheel cell
  int targetCell1 = 13;
  int targetCell2 = 11;
  int targetCell3 = 14;
    
  const std::vector<std::vector<int>> reelsData = {
    jsonData1,
    jsonData2,
    jsonData3
  };
    
  _targetCellsCounter = 0;
  _firstTargetCells = true;
  std::vector<std::vector<int>> targetCells = { {targetCell1, targetCell2, targetCell3 },
                                                        { 11, 14, 15 },
                                                        { 5, 7, 19 },
                                                        { 1, 19, 17 } };
  _currentBet = 100;

  // Reel
  Reel* reel = Reel::create(reelsData);
  _reel = reel;
  reel->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
  this->addChild(reel, 40);
    
  // SlotMachineLogic
  SlotMachineLogic* sMLogic = SlotMachineLogic::create(reelsData);
  _sMLogic = std::move(sMLogic);
  this->addChild(_sMLogic);
    
    int win = 500;
    bool firstSpin = true;
    // Callback spinFinished
    reel->setOnSpinFinished([this, reelsData, targetCells, firstSpin](int win) mutable {
        
    // callback
    _sMLogic->spinFinished(win);
    _sMLogic->spinEnded(reelsData, targetCells[_targetCellsCounter], _currentBet);
    _sMLogic->calculateWin(_currentBet);
        
    if (_balanceLabel)
    {
      _balanceLabel->setString(
      "Balance: " + std::to_string(_sMLogic->getBalance())
      );
    }
    });
    
  //create spin button
  auto spinButton = Button::create(Constants::SPIN_BUTTON_NORMAL
                                     , Constants::SPIN_BUTTON_SELECTED, Constants::SPIN_BUTTON_NORMAL);
  Size buttonSize = spinButton->getContentSize();
  spinButton->setPosition(Vec2(visibleSize.width + origin.x - 0.6 * buttonSize.width, -0.6 * buttonSize.height));
  spinButton->setPressedActionEnabled(true);
  this->addChild(spinButton, 40);
  // spin text label
  auto spinLabel = Label::createWithTTF("SPIN", "fonts/Marker Felt.ttf", 10);
  spinLabel->setPosition(Vec2(0.4 * buttonSize.width , 1.3 * buttonSize.height));
  spinButton->addChild(spinLabel, 3);
    
    
    spinButton->addTouchEventListener([this, reelsData, targetCells, firstSpin] (Ref* pSender,
                                                                                  Widget::TouchEventType type) mutable
    {
        if (type == Widget::TouchEventType::ENDED)
        {
            if(_reel->allWheelsStopped() == true) {
                // Not enough balance!
                if(!_sMLogic->play())
                {
                    return;
                }
                if(!firstSpin && _targetCellsCounter < (targetCells.size()-1)) {
                  _targetCellsCounter++;
                } else {
                    _targetCellsCounter = 0;
                    firstSpin = false;
                }
            }
            _reel->startStopMachine(targetCells[_targetCellsCounter]);
        }
    });

  auto move = MoveBy::create(1, Vec2(0, 1.2 * buttonSize.height));
  // create a Ease Elastic Out Action
  auto move_ease_out = EaseElasticOut::create(move->clone());
  auto seq = Sequence::create(move_ease_out, nullptr);
  spinButton->runAction(seq);
    
  //create bet button
  auto betButton = Button::create(Constants::SPIN_BUTTON_NORMAL
                                       , Constants::SPIN_BUTTON_SELECTED, Constants::SPIN_BUTTON_NORMAL);
  Size buttonSize1 = betButton->getContentSize();
    
  betButton->setPosition(Vec2(visibleSize.width + origin.x - 1.8 * buttonSize1.width, 0.65 * buttonSize1.height));
  betButton->setPressedActionEnabled(true);
  this->addChild(betButton, 40);
  betButton->addTouchEventListener([this](Ref* pSender, Widget::TouchEventType type){
    if (type == Widget::TouchEventType::ENDED)
    {
        int currentBet = _sMLogic->increaseBet(100);
        _currentBet = currentBet;
        _betCountLabel->setString(std::to_string(currentBet));
    }
  });
    
  // bet text label
  auto betLabel = Label::createWithTTF("BET", "fonts/Marker Felt.ttf", 10);
  betLabel->setPosition(Vec2(0.4 * buttonSize1.width , 1.2 * buttonSize1.height));
  betButton->addChild(betLabel, 50);
    
  auto betCountLabel = Label::createWithTTF("100", "fonts/Marker Felt.ttf", 15);
  betCountLabel->setPosition(Vec2(visibleSize.width + origin.x - 3.1 * buttonSize1.width, 0.65 * buttonSize1.height));
  this->addChild(betCountLabel, 50);
  _betCountLabel = betCountLabel;
    
  // balance
  auto balanceLabel = Label::createWithTTF("Balance: ", "fonts/Marker Felt.ttf", 15);
  balanceLabel->setPosition(Vec2(0.8 * visibleSize.width + origin.x, 0.95 * visibleSize.height + origin.y));
  this->addChild(balanceLabel, 50);
  _balanceLabel = balanceLabel;
    
    if (_balanceLabel)
    {
      _balanceLabel->setString(
        "Balance: " + std::to_string(_sMLogic->getBalance())
      );
    }
  
  return true;
}

