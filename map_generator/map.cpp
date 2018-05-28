#include "map.h"
#include "map_object\map_object.h"

USING_NS_CC;

MapLayer* MapLayer::create(std::vector<std::vector<Configure::MAP_OBJECT>>&& mapinfo)
{
	MapLayer* ref = new MapLayer();

	if (ref && ref->init(std::move(mapinfo)))
	{
		ref->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ref);
	}
	return ref;
}

bool MapLayer::init(std::vector<std::vector<Configure::MAP_OBJECT>>&& mapinfo)
{
	if (!Layer::init())
	{
		return false;
	}

	_mapInfo = mapinfo;
	Vec2 pos;
	//mapping object
	for (auto& row : _mapInfo)
	{
		for (auto& col : row)
		{
			//mapping base
			Ground* base = Ground::create("ground_sand_000");
			base->setPosition(pos);
			pos.x += base->getContentSize().width;

			if (col == Configure::MAP_OBJECT::FENCE)
			{
				//mapping fence
				Fence* fence = Fence::create("fence");
				fence->setTag(static_cast<uint8_t>(Configure::MAP_OBJECT::FENCE));
				fence->setPosition(Configure::g_baseWidth / 2, Configure::g_baseHeight / 2);
				//fence->setRotation(random(0.0f, 359.0f));
				base->addChild(fence);
			}
			else if (col == Configure::MAP_OBJECT::HAY)
			{
				//mapping hay
				Hay* hay = Hay::create("hay");
				hay->setTag(static_cast<uint8_t>(Configure::MAP_OBJECT::HAY));
				hay->setPosition(Configure::g_baseWidth / 2, Configure::g_baseHeight / 2);
				hay->setRotation(random(0.0f, 359.0f));
				base->addChild(hay);
			}			
			this->addChild(base);
		}
		pos.x = 0.0f;
		pos.y += Configure::g_baseHeight;
	}

	return true;
}

MapLayer::MapLayer(void)
{

}

MapLayer::~MapLayer(void)
{

}