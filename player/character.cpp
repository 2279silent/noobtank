#include <math.h>
#include "map_generator\map_object\map_object.h"
#include"character.h"

USING_NS_CC;

Tank* Tank::create(Configure::TANKCOLOR color)
{
	Tank* ref = new Tank();

	if (ref && ref->init(color))
	{
		ref->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ref);
	}

	return ref;
}

bool Tank::init(Configure::TANKCOLOR color)
{
	if (!Sprite::initWithSpriteFrameName(Configure::TankInfo::Name(color)))
	{
		return false;
	}
	this->setTag(static_cast<uint8_t>(Configure::MAP_OBJECT::TANK));

	PhysicsBody* body = PhysicsBody::createBox(this->getContentSize(), PhysicsMaterial(0.0f,1.0f,0.0f));
	body->setGravityEnable(false);
	body->setCategoryBitmask(0x08);
	body->setCollisionBitmask(0x02);
	body->setContactTestBitmask(0x02);
	this->setPhysicsBody(body);

	_barrel = nullptr;
	_color = color;
	_bulletSpeed = 3.0f;

	SetBarrel();
	_barrel->setAnchorPoint(Vec2(0.5f, 0.15f));
	_barrel->setNormalizedPosition(Vec2(0.5f, 0.5f));
	this->addChild(_barrel);

	return true;
}

Bullet* Tank::Attack(void)
{
	Bullet* bullet = Bullet::create(_color);
	bullet->setAnchorPoint(Vec2(0.5f, 0.0f));
	bullet->setRotation(this->getRotation() + _barrel->getRotation());

	//calculate vector
	Vec2 u(0.0f, 1.0f);
	Vec2 v = u.rotateByAngle(Vec2(0.0f, 0.0f), -(this->getRotation() + _barrel->getRotation())*3.14159f / 180.0f);
	bullet->SetDirection(v*_bulletSpeed);

	return bullet;
}

void Tank::Aim(float angle)
{
	_barrel->setRotation(_barrel->getRotation() + angle);
}

void Tank::Move(cocos2d::Vec2 direction)
{
	Vec2 unitVec(0.0f, 1.0f);
	this->setRotation(direction.getAngle(unitVec)*180.0f/3.14159f);
	//this->setPosition(this->getPosition() + direction);
}

cocos2d::Vec2 Tank::AttackPoint(void)
{
	Vec2 attackPoint;

	attackPoint.x = _barrel->getContentSize().width / 2;
	attackPoint.y = _barrel->getContentSize().height;

	return _barrel->convertToWorldSpace(attackPoint);
}

void Tank::ChangeColor(void)
{
	switch (_color)
	{
	case Configure::TANKCOLOR::RED:		_color = Configure::TANKCOLOR::GREEN;	break;
	case Configure::TANKCOLOR::GREEN:	_color = Configure::TANKCOLOR::BLUE;	break;
	case Configure::TANKCOLOR::BLUE:	_color = Configure::TANKCOLOR::RED;		break;
	default:		break;
	}

	this->setSpriteFrame(Configure::TankInfo::Name(_color));
	SetBarrel();
}

void Tank::SetBarrel(void)
{
	if (_barrel == nullptr)
	{
		_barrel = Sprite::create();
	}
	switch (_color)
	{
	case Configure::TANKCOLOR::RED:		_barrel->setSpriteFrame("tank_red_barrel");		break;
	case Configure::TANKCOLOR::GREEN:	_barrel->setSpriteFrame("tank_green_barrel");	break;
	case Configure::TANKCOLOR::BLUE:	_barrel->setSpriteFrame("tank_blue_barrel");	break;
	default:		break;
	}
}