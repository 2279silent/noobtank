#pragma once

#include "cocos2d.h"

class GameMain : public cocos2d::Scene
{
public:
	static GameMain* GetInstance(void);

	bool init(void);
private:
	static GameMain* _gamemain;

	GameMain(void);
	~GameMain(void);
};