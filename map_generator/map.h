#pragma once

#include <vector>
#include "cocos2d.h"
#include "../configure.h"

class MapLayer :public cocos2d::Layer
{
public:
	static MapLayer* create(std::vector<std::vector<Configure::MAP_OBJECT>>&& mapinfo);

	bool init(std::vector<std::vector<Configure::MAP_OBJECT>>&& mapinfo);
protected:
	MapLayer(void);
	~MapLayer(void);

	std::vector<std::vector<Configure::MAP_OBJECT>> _mapInfo;
};