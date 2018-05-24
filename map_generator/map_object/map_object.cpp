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
	if (!Sprite::initWithSpriteFrameName(_spriteName))
	{
		return false;
	}

	_interactive = false;
	_health = -1;
	_damage = 0;

	return true;
}

bool MapObjectImp::Interactive(void)
{
	return _interactive;
}

int32_t MapObjectImp::Damage(void)
{
	return _damage;
}

int32_t MapObjectImp::Health(void)
{
	return _health;
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

	_interactive = true;
	_health = static_cast<int32_t> (Configure::Health::BASIC);

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
	Bullet* ref = new Bullet((color));

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
	_interactive = true;
	_damage = Configure::TankInfo::Damage(color);

	return true;
}

Bullet::Bullet(Configure::TANKCOLOR color)
	:MapObjectImp(Configure::TankInfo::Name(color))
{
	
}
Bullet::~Bullet(void)
{

}