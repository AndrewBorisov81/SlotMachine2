#include "GameField.h"
#include "SlotMachine.h"
//#include "SimpleAudioEngine.h"
#include "Constants.h"
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
    
  // When to stop wheel cell
  int targetCell = 12;
    
  //Frame Slot Machine
  auto frameSprite = Sprite::create(Constants::FRAME_WHEEL);
  frameSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
  this->addChild(frameSprite, 40);
    
  Size frameSize = frameSprite->getContentSize();
    
  //slot machine
  SlotMachine* slotMachine1 = new SlotMachine(jsonData1);
  slotMachine1->setPosition(Vec2(0.19 * frameSize.width, 0.5 * frameSize.height));
  frameSprite->addChild(slotMachine1, 30);
  _slotMachine1 = slotMachine1;
    
  //slot machine
  SlotMachine* slotMachine2 = new SlotMachine(jsonData2);
  slotMachine2->setPosition(Vec2(0.38 * frameSize.width, 0.5 * frameSize.height));
  frameSprite->addChild(slotMachine2, 30);
  _slotMachine2 = slotMachine2;
    
  //slot machine
  SlotMachine* slotMachine3 = new SlotMachine(jsonData1);
  slotMachine3->setPosition(Vec2(0.57 * frameSize.width, 0.5 * frameSize.height));
  frameSprite->addChild(slotMachine3, 30);
  _slotMachine3 = slotMachine3;

  //create spin button
    auto spinButton = Button::create(Constants::SPIN_BUTTON_NORMAL
                                     , Constants::SPIN_BUTTON_SELECTED, Constants::SPIN_BUTTON_NORMAL);
  Size buttonSize = spinButton->getContentSize();
  spinButton->setPosition(Vec2(visibleSize.width + origin.x - 0.6 * buttonSize.width, -0.6 * buttonSize.height));
  spinButton->setPressedActionEnabled(true);
    
    spinButton->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type){
    if (type == Widget::TouchEventType::ENDED)
    {
      slotMachine1->startStopMachine(targetCell);
           
      this->runAction(Sequence::create(DelayTime::create(0.2f), CallFunc::create([this]() {
        this->_slotMachine2->startStopMachine(10);}), nullptr));
          
      this->runAction(Sequence::create(DelayTime::create(0.4f),   // delay in seconds
        CallFunc::create([this]() { this->_slotMachine3->startStopMachine(17); }),
          nullptr));
           
        }
    });
  this->addChild(spinButton, 40);

  auto move = MoveBy::create(1, Vec2(0, 1.2 * buttonSize.height));
  // create a Ease Elastic Out Action
  auto move_ease_out = EaseElasticOut::create(move->clone());
  auto seq = Sequence::create(move_ease_out, nullptr);
  spinButton->runAction(seq);

    return true;
}
