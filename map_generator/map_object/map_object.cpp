#include "../../gamemain.h"
#include "map_object.h"

USING_NS_CC;

MapObjectImp* MapObjectImp::create(std::string spriteName)
{
	MapObjectImp* ref = new MapObjectImp(spriteName);

	if (ref && ref->init())
	{
		ref->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ref);
	}
	return ref;
}

bool MapObjectImp::init(void)
{
	if (_spriteName.empty())
	{
		if (!Sprite::init())
		{
			return false;
		}		
	}
	else if (!Sprite::initWithSpriteFrameName(_spriteName))
	{
		return false;
	}

	_health = -1;
	_damage = 0;
	_interactive = false;

	return true;
}

int32_t MapObjectImp::Damage(void)
{
	return _damage;
}

void MapObjectImp::Injure(int32_t value)
{
	if (_interactive)
	{
		_health -= value;
		if (_health < 0)
		{
			_health = 0;
		}
	}
}

int32_t MapObjectImp::Health(void)
{
	return _health;
}

bool MapObjectImp::InterActive(void)
{
	return _interactive;
}

MapObjectImp::MapObjectImp(const std::string& spriteName)
	:_spriteName(spriteName)
{

}

MapObjectImp::~MapObjectImp(void)
{

}

Hay* Hay::create(const std::string& spriteName)
{
	Hay* ref = new Hay(spriteName);

	if (ref && ref->init())
	{
		ref->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ref);
	}
	return ref;
}

bool Hay::init(void)
{
	if (!MapObjectImp::init())
	{
		return false;
	}
	this->setTag(static_cast<uint8_t>(Configure::MAP_OBJECT::HAY));

	PhysicsBody* body = PhysicsBody::createBox(this->getContentSize());
	body->setDynamic(false);
	body->setCategoryBitmask(0x01);
	body->setCollisionBitmask(0x04);
	body->setContactTestBitmask(0x04);
	this->setPhysicsBody(body);

	_health = static_cast<int32_t> (Configure::Health::BASIC);
	_interactive = true;

	return true;
}

Hay::Hay(const std::string& spriteName)
	:MapObjectImp(spriteName)
{

}
Hay::~Hay(void)
{

}

Fence* Fence::create(const std::string& spriteName)
{
	Fence* ref = new Fence(spriteName);

	if (ref && ref->init())
	{
		ref->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ref);
	}
	return ref;
}

bool Fence::init(void)
{
	if (!MapObjectImp::init())
	{
		return false;
	}
	this->setTag(static_cast<uint8_t>(Configure::MAP_OBJECT::FENCE));

	PhysicsBody* body = PhysicsBody::createBox(this->getContentSize(), PhysicsMaterial(0.0f, 1.0f, 0.0f));
	body->setDynamic(false);
	body->setCategoryBitmask(0x02);
	body->setCollisionBitmask(0x0c);
	body->setContactTestBitmask(0x04);
	this->setPhysicsBody(body);
	return true;
}

Fence::Fence(const std::string& spriteName)
	:MapObjectImp(spriteName)
{

}
Fence::~Fence(void)
{

}

Ground* Ground::create(const std::string& spriteName)
{
	Ground* ref = new Ground(spriteName);

	if (ref && ref->init())
	{
		ref->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ref);
	}
	return ref;
}

bool Ground::init(void)
{
	if (!MapObjectImp::init())
	{
		return false;
	}
	this->setAnchorPoint(Vec2(0.0f, 0.0f));
	return true;
}

Ground::Ground(const std::string& spriteName)
	:MapObjectImp(spriteName)
{

}
Ground::~Ground(void)
{

}

Bullet* Bullet::create(Configure::TANKCOLOR color)
{
	Bullet* ref = new Bullet();

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

bool Bullet::init(Configure::TANKCOLOR color)
{
	if (!MapObjectImp::init())
	{
		return false;
	}
	this->setSpriteFrame(Configure::BulletInfo::Name(color));
	this->setTag(static_cast<uint8_t>(Configure::MAP_OBJECT::BULLET));

	PhysicsBody* body = PhysicsBody::createBox(this->getContentSize());
	body->setGravityEnable(false);
	body->setCategoryBitmask(0x04);
	body->setCollisionBitmask(0x03);
	body->setContactTestBitmask(0x03);
	this->setPhysicsBody(body);

	_interactive = true;
	_damage = Configure::BulletInfo::Damage(color);

	return true;
}

void Bullet::SetDirection(cocos2d::Vec2 vector)
{
	if (vector.isZero() == false)
	{
		_vector = vector;
		this->schedule(CC_SCHEDULE_SELECTOR(Bullet::OnFly, this));
	}
}

void Bullet::OnFly(float dt)
{
	Vec2 position = this->getPosition() + _vector;
	this->setPosition(position);

	auto scene = Director::getInstance()->getRunningScene();
	auto viewSize = scene->getContentSize();
	auto tank = scene->getChildByTag(static_cast<uint32_t>(Configure::MAP_OBJECT::TANK));

	Rect visibleRect(tank->getPosition()- Vec2(viewSize/2), viewSize);
	if (visibleRect.containsPoint(position) == false)
	{
		this->removeFromParent();
	}		
}

Bullet::Bullet(void)
{
	
}
Bullet::~Bullet(void)
{

}