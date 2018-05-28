#pragma once

#include "cocos2d.h"

class Tank;
class Bullet;
class GameMain;

class Controler
{
public:
	virtual void Enable(void) = 0;
	virtual void Disable(void) = 0;
};

class TankControler :public Controler
{
public:
	TankControler(Tank* tank = nullptr);
	~TankControler(void);

	void update(float dt);
	void SetTank(Tank* tank);
	inline Tank* GetTank(void) { return _tank; }

	void Enable(void);
	void Disable(void);
protected:

	void OnKeyPressed(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event);
	void OnKeyReleased(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event);

	cocos2d::EventListenerKeyboard* _keyboardListener;

	Tank* _tank;
	cocos2d::Vec2 _direction;
	float _attackPeriod;
	float _periodRec;
	bool _attack;
};