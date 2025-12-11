#ifndef __SLOT_MACHINE_H__
#define __SLOT_MACHINE_H__

#include "cocos2d.h"

class Wheel;


class SlotMachine: public cocos2d::Node
{

public:
  SlotMachine(std::vector<int> boxData);

  void startStopMachine();

  void update(float) override;

  float easyIn(float t);

  float easeOutBack(float t, float s = 1.70158f);

  //easing tests
  inline float easeInElasticHelper_(float t, float b, float c, float d, float a, float p);
  inline float easeInElastic(float t, float amplitude, float period);

  inline float easeOutElasticHelper_(float t, float /*b*/, float c, float /*d*/, float a, float p);
  inline float easeOutElastic(float t, float amplitude, float period);

  inline float easeOutBounceHelper_(float t, float c, float a);
  inline float easeOutBounce(float t, float a = 1.70158f);


private:
  std::vector<int> _boxData;

  Wheel* _wheel;

  cocos2d::Size _cellSize{ 0, 0 };

  int _counterCellsWheelMoveDown { 0 };

  cocos2d::Vec2 _wheelInitPos { 0, 0 };

  bool _fMachineStart { false };

  bool _fMove { false };
  bool _isStopped { true };
  bool _break { false };
  bool _start { false };

  cocos2d::Vec2 _moveDirection{ 0, -1 };

  //start
  float _deltaShiftWheelPos{ 2 };
  float _maxShiftPos{ 10 };

  float _timerEasyIn{ 0 };
  float _deltaTimeEasyIn{ 0.05f };

  float _kEasyIn{ 0 };

  //break
  float _breakDistance { 0 };
  
  float _fCalculateBreakDistance{ false };

  float _deltaTimeBreak { 0.05f };
  float _timerBreak { 0 };

  float _kSlowDownBack { 0 };

  float _initPosYBreak { 0 };

  float _shiftSetPosBreakKSlowBack { 0 };

  int _counterKBreak { 0 };
};

#endif //__SLOT_MACHINE_H__
