#include "gamemain.h"
#include "map_generator\map.h"
#include "player\character.h"
#include "map_generator\map_object\map_object.h"

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
	if (!Scene::initWithPhysics())
	{
		return false;
	}
	_eventDispatcher = Director::getInstance()->getEventDispatcher();
	//load resource
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("image/image_all.plist");
	//get visible size
	_mapSize = Director::getInstance()->getVisibleSize();
	_BG = Layer::create();
	_BG->setContentSize(this->getContentSize());
	this->addChild(_BG, -1);

	//build map
	for (int rowIndex =0; rowIndex<_environment.size(); rowIndex++)
	{
		for (int colIndex=0; colIndex<_environment.at(rowIndex).size();colIndex++)
		{
			MapLayer* layer = _mapGenerator.CreateMap();
			layer->setPosition((colIndex - 1)* _mapSize.width, (rowIndex - 1)* _mapSize.height);
			_BG->addChild(layer);

			_environment.at(rowIndex).at(colIndex) = layer;
		}
	}
	
	Tank* player = Tank::create(Configure::TANKCOLOR::RED);
	player->setPositionNormalized(Vec2(0.5f, 0.5f));
	this->addChild(player);
	_tankControler.SetTank(player);

	_evenContact = EventListenerPhysicsContact::create();
	_evenContact->onContactBegin = CC_CALLBACK_1(GameMain::OnContactBegin, this);
	_evenContact->onContactSeparate = CC_CALLBACK_1(GameMain::OnContactSeperate, this);
	_eventDispatcher->addEventListenerWithFixedPriority(_evenContact, 1);

	this->scheduleUpdate();

	return true;
}

void GameMain::update(float dt)
{
	Vec2 position = _BG->getPosition();
	Size size = _BG->getContentSize();

	if (position.x < _environment.at(0).at(0)->getPositionX())
	{
		for (int rowIndex = 0; rowIndex<_environment.size(); rowIndex++)
		{
			_environment.at(rowIndex).at(0)->removeFromParent();
			for (int colIndex = 0; colIndex<_environment.at(rowIndex).size()-1; colIndex++)
			{
				_environment.at(rowIndex).at(colIndex) = _environment.at(rowIndex).at(colIndex + 1);
			}
			MapLayer* layer = _mapGenerator.CreateMap();
			_BG->addChild(layer);
			_environment.at(rowIndex).at(2) = layer;
		}
		_BG->setPositionX(0.0f);
	}
	else if (position.x > _environment.at(0).at(2)->getPositionX())
	{
		for (int rowIndex = 0; rowIndex<_environment.size(); rowIndex++)
		{
			_environment.at(rowIndex).at(2)->removeFromParent();
			for (int colIndex = 2; colIndex > 0; colIndex--)
			{
				_environment.at(rowIndex).at(colIndex) = _environment.at(rowIndex).at(colIndex-1);
			}
			MapLayer* layer = _mapGenerator.CreateMap();
			_BG->addChild(layer);
			_environment.at(rowIndex).at(0) = layer;
		}
		_BG->setPositionX(0.0f);
	}
	else if (position.y > _environment.at(2).at(0)->getPositionY())
	{
		for (int colIndex = 0; colIndex<_environment.at(0).size(); colIndex++)
		{
			_environment.at(2).at(colIndex)->removeFromParent();
			for (int rowIndex = 2; rowIndex > 0; rowIndex--)
			{
				_environment.at(rowIndex).at(colIndex) = _environment.at(rowIndex-1).at(colIndex);
			}
			MapLayer* layer = _mapGenerator.CreateMap();
			_BG->addChild(layer);
			_environment.at(0).at(colIndex) = layer;
		}
		_BG->setPositionY(0.0f);
	}
	else if (position.y < _environment.at(0).at(0)->getPositionY())
	{
		for (int colIndex = 0; colIndex < _environment.at(0).size(); colIndex++)
		{
			_environment.at(0).at(colIndex)->removeFromParent();
			for (int rowIndex = 0; rowIndex < _environment.at(0).size()-1; rowIndex++)
			{
				_environment.at(rowIndex).at(colIndex) = _environment.at(rowIndex + 1).at(colIndex);
			}
			MapLayer* layer = _mapGenerator.CreateMap();
			_BG->addChild(layer);
			_environment.at(2).at(colIndex) = layer;
		}
		_BG->setPositionY(0.0f);
	}
	for (int rowIndex = 0; rowIndex<_environment.size(); rowIndex++)
	{
		for (int colIndex = 0; colIndex<_environment.at(rowIndex).size(); colIndex++)
		{
			_environment.at(rowIndex).at(colIndex)->setPosition((colIndex - 1)* _mapSize.width, (rowIndex - 1)* _mapSize.height);
		}
	}
}

void GameMain::MapMove(cocos2d::Vec2 dir)
{
	_BG->setPosition(_BG->getPosition() + dir);
}

bool GameMain::OnContactBegin(PhysicsContact& contact)
{
	Node* nodeA = contact.getShapeA()->getBody()->getNode();
	Node* nodeB = contact.getShapeB()->getBody()->getNode();

	if (nodeA->getTag() == static_cast<uint8_t>(Configure::MAP_OBJECT::BULLET))
	{
		Bullet* bullet = static_cast<Bullet*>(nodeA);
		MapObjectImp* target = static_cast<MapObjectImp*>(nodeB);

		if (target->InterActive())
		{
			target->Injure(bullet->Damage());
			if (target->Health() == 0)
			{
				target->removeFromParent();
			}
		}
		bullet->removeFromParent();
	}
	else if (nodeB->getTag() == static_cast<uint8_t>(Configure::MAP_OBJECT::BULLET))
	{
		Bullet* bullet = static_cast<Bullet*>(nodeB);
		MapObjectImp* target = static_cast<MapObjectImp*>(nodeA);

		if (target->InterActive())
		{
			target->Injure(bullet->Damage());
			if (target->Health() == 0)
			{
				target->removeFromParent();
			}
		}
		bullet->removeFromParent();
	}
	return false;
}

bool GameMain::OnContactSeperate(cocos2d::PhysicsContact& contact)
{
	Node* nodeA = contact.getShapeA()->getBody()->getNode();
	Node* nodeB = contact.getShapeB()->getBody()->getNode();

	//if (nodeA->getTag() == static_cast<uint8_t>(Configure::MAP_OBJECT::TANK))
	//{
	//	if (nodeB->getTag() == static_cast<uint8_t>(Configure::MAP_OBJECT::FENCE))
	//	{
	//		static_cast<Tank*>(nodeA)->UnBlock();
	//	}
	//}
	//else if (nodeB->getTag() == static_cast<uint8_t>(Configure::MAP_OBJECT::TANK))
	//{
	//	if (nodeA->getTag() == static_cast<uint8_t>(Configure::MAP_OBJECT::FENCE))
	//	{
	//		static_cast<Tank*>(nodeA)->UnBlock();
	//	}
	//}
	return false;
}

GameMain::GameMain(void)
{

}

GameMain::~GameMain(void)
{

}