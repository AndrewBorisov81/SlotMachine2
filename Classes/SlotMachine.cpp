#include "SlotMachine.h"
#include "Wheel.h"
#include "Constants.h"
//#include "SimpleAudioEngine.h"
#include <cmath>

USING_NS_CC;

SlotMachine::SlotMachine(const std::vector<int>& boxData, int targetCell): _boxData(boxData), _targetCell{targetCell}
{
  //Create wheel
  Wheel* wheel = new Wheel(_boxData);
  this->addChild(wheel);

  _wheel = wheel;

  Size cellSize = wheel->getCellSize();
  _cellSize = cellSize;

  Vec2 wheelPos = Vec2(0, -cellSize.height);
  wheel->setPosition(wheelPos);

  this->scheduleUpdate();
}

void SlotMachine::startStopMachine()
{
  _fMachineStart = (_fMachineStart) ? false : true;

  if (_fMove && !_isStopped)
  {
    _break = true;
    _start = false;
  }
    

  if (_isStopped)
  {
    _fMove = (_fMachineStart) ? true : false;

    if (_fMove)
    {
      _isStopped = false;
      _start = true;
      _break = false;
      _fCalculateBreakDistance = false;
    }
  }
}

void SlotMachine::update(float delta)
{
  //move wheel
  if (_fMove)
  {
    Vec2 wheelPos = _wheel->getPosition();

    //start
    if (_start)
    {
      if (_timerEasyIn < 1)
      {
        _timerEasyIn += _deltaTimeEasyIn;
        if(getState() != State::START)
        {
          setState(State::START);
        }
      }
      else if(_state != State::SPIN)
      {
        _timerEasyIn = 1;
        setState(State::SPIN);
      }

      _kEasyIn = easyIn(_timerEasyIn);
      _deltaShiftWheelPos = _kEasyIn * _maxShiftPos;

      wheelPos.y -= _deltaShiftWheelPos;

      _wheel->setPosition(wheelPos);
    }


    //break
    if (_break)
    {
      int indLastCellBreak = _wheel->getIndexLastCell();

      if (!_fCalculateBreakDistance)
      {
        _initPosYBreak = wheelPos.y;

        float breakDistance = wheelPos.y + (indLastCellBreak - 1) * _cellSize.height;
        _breakDistance = breakDistance;

        _fCalculateBreakDistance = true;

        _timerEasyIn = 0;
      }

      _timerBreak += _deltaTimeBreak;

      _kSlowDownBack = easeOutBack(_timerBreak);
      //_kSlowDownBack = easeInElastic(_timerBreak, 1, 0.5);
      //_kSlowDownBack = easeOutElastic(_timerBreak, 1, 0.5);
      //_kSlowDownBack = easeOutBounce(_timerBreak);

      _shiftSetPosBreakKSlowBack = _initPosYBreak - (_kSlowDownBack * _breakDistance);

      _wheel->setPosition(Vec2(0,_shiftSetPosBreakKSlowBack));

      if (_timerBreak >= 1 && _state != State::BREAK)
      {
        _isStopped = true;
        _fMove = false;
        setState(State::STOP);

        _timerBreak = 0;
        _kSlowDownBack = 0;
        _shiftSetPosBreakKSlowBack = 0;
        _initPosYBreak = 0;
      }
    }


    //check add delete cell
    int indLastCell = _wheel->getIndexLastCell();
    float dist1 = wheelPos.y + (indLastCell - 1) * _cellSize.height;

    if (dist1 <= _cellSize.height)
    {
      _wheel->addCell();
      _wheel->deleteCell();

      _counterCellsWheelMoveDown++;


      //set init position wheel(Y axis)
      if (_counterCellsWheelMoveDown == 10 && !_break)
      {
        float deltaShiftY = _counterCellsWheelMoveDown * _cellSize.height;

        Vec2 wheelPos2 = _wheel->getPosition();
        wheelPos2.y += deltaShiftY;
        _wheel->setPosition(wheelPos2);

        //shift cell int deltaShiftY
        _wheel->moveCellsInitPos(deltaShiftY);

        _counterCellsWheelMoveDown = 0;
      }
    }
  }
}

float SlotMachine::easyIn(float t)
{
  return t;
}

float SlotMachine::easeOutBack(float t, float s)
{
  //easyOutBack
  t -= 1;
  return (t*t*((s + 1)*t + s) + 1);

  //easyInCubic
  /*t -= 1;
  return t * t*t + 1;*/

  //easeInBack
  //return t * t * ((s + 1)*t - s);

  //easyInOutBack
  /*t *= 2;
  if (t < 1) {
    s *= 1.525f;
    return 0.5f*(t*t*((s + 1)*t - s));
  }
  else {
    t -= 2;
    s *= 1.525f;
    return 0.5f*(t*t*((s + 1)*t + s) + 2);
  }*/
}

//! \cond
float SlotMachine::easeInElasticHelper_(float t, float b, float c, float d, float a, float p)
{
  if (t == 0) return b;
  float t_adj = t / d;
  if (t_adj == 1) return b + c;

  float s;
  if (a < std::abs(c)) {
    a = c;
    s = p / 4.0f;
  }
  else {
    s = p / (2 * (float)M_PI) * std::asin(c / a);
  }

  t_adj -= 1;
  return -(a * std::pow(2, 10 * t_adj) * std::sin((t_adj*d - s)*(2 * (float)M_PI) / p)) + b;
}

float SlotMachine::easeInElastic(float t, float amplitude, float period)
{
  return easeInElasticHelper_(t, 0, 1, 1, amplitude, period);
}


float SlotMachine::easeOutElasticHelper_(float t, float /*b*/, float c, float /*d*/, float a, float p)
{
  if (t == 0) return 0;
  if (t == 1) return c;

  float s;
  if (a < c) {
    a = c;
    s = p / 4;
  }
  else {
    s = p / (2 * (float)M_PI) * std::asin(c / a);
  }

  return a * std::pow(2, -10 * t) * std::sin((t - s)*(2 * (float)M_PI) / p) + c;
}

//! Easing equation for an elastic (exponentially decaying sine wave) ease-out, decelerating from zero velocity.
float SlotMachine::easeOutElastic(float t, float amplitude, float period)
{
  return easeOutElasticHelper_(t, 0, 1, 1, amplitude, period);
}

//! Easing equation for a bounce (exponentially decaying parabolic bounce) ease-out, decelerating from zero velocity. The \a a parameter controls overshoot, the default producing a 10% overshoot.
float SlotMachine::easeOutBounce(float t, float a)
{
  return easeOutBounceHelper_(t, 1, a);
}

//! \cond
float SlotMachine::easeOutBounceHelper_(float t, float c, float a)
{
  if (t == 1) return c;
  if (t < (4 / 11.0f)) {
    return c * (7.5625f*t*t);
  }
  else if (t < (8 / 11.0f)) {
    t -= (6 / 11.0f);
    return -a * (1 - (7.5625f*t*t + 0.75f)) + c;
  }
  else if (t < (10 / 11.0f)) {
    t -= (9 / 11.0f);
    return -a * (1 - (7.5625f*t*t + 0.9375f)) + c;
  }
  else {
    t -= (21 / 22.0f);
    return -a * (1 - (7.5625f*t*t + 0.984375f)) + c;
  }
}
//! \endcond
void SlotMachine::setState(State state)
{
    _state = state;
}
  
SlotMachine::State SlotMachine::getState() const
{
    return _state;
}
