#pragma once

#include"cocos2d.h"
#include"../configure.h"

class Bullet;

class Character
{
public:
	virtual Bullet* Attack(void) = 0;
	virtual void Aim(float angle) = 0;
	virtual void Move(cocos2d::Vec2 direction) = 0;
};

class Tank :public Character, public cocos2d::Sprite
{
public:
	static Tank* create(Configure::TANKCOLOR color);

	bool init(Configure::TANKCOLOR color);

	virtual Bullet* Attack(void)override;
	virtual void Aim(float angle)override;
	virtual void Move(cocos2d::Vec2 direction)override;

	void ChangeColor(void);

	cocos2d::Vec2 AttackPoint(void);
protected:
	Tank(void){}
	virtual~Tank(void){}

	void SetBarrel(void);

	cocos2d::Sprite* _barrel;
	Configure::TANKCOLOR _color;

	float _bulletSpeed;
};