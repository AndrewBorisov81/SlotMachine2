#include "GameField.h"
#include "SlotMachine.h"
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
  int targetCell1 = 12;
  int targetCell2 = 14;
  int targetCell3 = 9;
    
  const std::vector<std::vector<int>> reelData = {
    jsonData1,
    jsonData2,
    jsonData3
  };
    
  const std::vector<int> targetCells = { targetCell1, targetCell2, targetCell3 };

  // Reel
  Reel* reel = Reel::create(reelData);
  reel->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
  this->addChild(reel, 40);
    
  //Frame Slot Machine
  auto frameSprite = Sprite::create(Constants::FRAME_WHEEL);
  frameSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
  //this->addChild(frameSprite, 40);
    
  Size frameSize = frameSprite->getContentSize();
    
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
    

    spinButton->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type){
        if (type == Widget::TouchEventType::ENDED)
        {
            reel->startStopMachine(targetCells);
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
  betButton->setPosition(Vec2(visibleSize.width + origin.x - 2 * buttonSize1.width, 0.65 * buttonSize1.height));
  betButton->setPressedActionEnabled(true);
  this->addChild(betButton, 40);
  // bet text label
  auto betLabel = Label::createWithTTF("BET", "fonts/Marker Felt.ttf", 10);
  betLabel->setPosition(Vec2(0.4 * buttonSize1.width , 1.2 * buttonSize1.height));
  betButton->addChild(betLabel, 50);
  
  return true;
}
