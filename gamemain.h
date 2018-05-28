#pragma once

#include<array>
#include<vector>
#include "cocos2d.h"
#include "map_generator\map_generator.h"
#include "UI\controler.h"

class MapLayer;

class GameMain : public cocos2d::Scene
{
public:
	static GameMain* GetInstance(void);

	bool init(void);

	void update(float dt)override;
	void MapMove(cocos2d::Vec2 dir);

	inline const std::array<std::array<MapLayer*, 3>, 3>& GetEnvironment(void) { return _environment; }
protected:
	bool OnContactBegin(cocos2d::PhysicsContact& contact);
	bool OnContactSeperate(cocos2d::PhysicsContact& contact);

	MapGenerator _mapGenerator;
	TankControler _tankControler;
	std::array<std::array<MapLayer*, 3>, 3> _environment;

	cocos2d::Size _mapSize;
	cocos2d::Layer* _BG;

	cocos2d::EventListenerPhysicsContact* _evenContact;
private:
	static GameMain* _gamemain;

	GameMain(void);
	~GameMain(void);
	
	cocos2d::EventDispatcher* _eventDispatcher;
};