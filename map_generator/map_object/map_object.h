#pragma once

#include <cstdint>
#include "cocos2d.h"
#include "../../configure.h"

class MapObject:public cocos2d::Sprite
{
public:
	virtual int32_t Damage(void) = 0;
	virtual void Injure(int32_t value) = 0;
	virtual int32_t Health(void) = 0;
	virtual bool InterActive(void) = 0;
protected:
	bool _interactive;
};

class MapObjectImp :public MapObject
{
public:
	static MapObjectImp* create(std::string spriteName);

	virtual bool init(void)override;
	virtual int32_t Damage(void)override;
	virtual void Injure(int32_t value)override;
	virtual int32_t Health(void)override;
	virtual bool InterActive(void)override;
protected:
	MapObjectImp(const std::string& spriteName = "");
	virtual~MapObjectImp(void);

	int32_t _health;
	int32_t _damage;
private:
	std::string _spriteName;
};

class Hay :public MapObjectImp
{
public:
	static Hay* create(const std::string& spriteName = "");

	virtual bool init(void)override;
protected:
	Hay(const std::string& spriteName = "");
	~Hay(void);
};

class Fence :public MapObjectImp
{
public:
	static Fence* create(const std::string& spriteName = "");

	virtual bool init(void)override;
protected:
	Fence(const std::string& spriteName = "");
	~Fence(void);
};

class Ground :public MapObjectImp
{
public:
	static Ground* create(const std::string& spriteName = "");

	virtual bool init(void)override;
protected:
	Ground(const std::string& spriteName = "");
	~Ground(void);
};

class Bullet :public MapObjectImp
{
public:
	static Bullet* create(Configure::TANKCOLOR color);

	virtual bool init(Configure::TANKCOLOR color);
	void SetDirection(cocos2d::Vec2 vector);
	void OnFly(float dt);
protected:
	Bullet(void);
	~Bullet(void);

	cocos2d::Vec2 _vector;
};
