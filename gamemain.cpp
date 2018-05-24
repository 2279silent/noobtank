#include "gamemain.h"
#include "map_generator\map.h"

USING_NS_CC;

GameMain* GameMain::_gamemain = nullptr;

GameMain* GameMain::GetInstance(void)
{
	if (_gamemain == nullptr)
	{
		_gamemain = new GameMain();
		if (_gamemain && _gamemain->init())
		{
			_gamemain->autorelease();
		}
		else
		{
			delete _gamemain;
			_gamemain = nullptr;
		}
	}
	return _gamemain;
}

bool GameMain::init(void)
{
	if (!Scene::init())
	{
		return false;
	}

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("image/image_all.plist");

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	std::vector<std::vector<Configure::MAP_OBJECT>>&& map = _mapGenerator.CreateMap();

	//map.resize(visibleSize.height / Configure::g_baseHeight);

	//for (auto& row : map)
	//{
	//	row.resize(visibleSize.width / Configure::g_baseWidth);
	//	for (auto& col : row)
	//	{
	//		col = static_cast<Configure::MAP_OBJECT>(random(0, 2));
	//	}
	//}

	MapLayer* layer = MapLayer::create(std::move(map));

	this->addChild(layer);

	return true;
}

GameMain::GameMain(void)
{

}

GameMain::~GameMain(void)
{

}