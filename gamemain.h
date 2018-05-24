#pragma once

#include "cocos2d.h"
#include "map_generator\map_generator.h"

class GameMain : public cocos2d::Scene
{
public:
	static GameMain* GetInstance(void);

	bool init(void);
protected:
	MapGenerator _mapGenerator;
private:
	static GameMain* _gamemain;

	GameMain(void);
	~GameMain(void);
};