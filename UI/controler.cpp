#include "../gamemain.h"
#include"../map_generator/map.h"
#include "controler.h"
#include "../player/character.h"
#include "../map_generator/map_object/map_object.h"

USING_NS_CC;

TankControler::TankControler(Tank* tank)
	:_tank(nullptr)
{
	if (tank)
	{
		_tank = tank;
		_tank->retain();
	}

	_attackPeriod = 0.25f;
	_periodRec = 0.0f;
	_attack = false;

	_keyboardListener = EventListenerKeyboard::create();
	_keyboardListener->onKeyPressed = CC_CALLBACK_2(TankControler::OnKeyPressed, this);
	_keyboardListener->onKeyReleased = CC_CALLBACK_2(TankControler::OnKeyReleased, this);

	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithFixedPriority(_keyboardListener, 1);

	Director::getInstance()->getScheduler()->scheduleUpdate(this, 0, false);
}

TankControler::~TankControler(void)
{
	if (_tank)
	{
		_tank->release();
		_tank = nullptr;
	}
}

void TankControler::update(float dt)
{
	if (_tank)
	{
		if (_direction.isZero() == false)
		{
			GameMain* gamemain = GameMain::GetInstance();
			gamemain->MapMove(-_direction);
			_tank->Move(_direction);
		}
		if (_attack)
		{
			_periodRec -= dt;
			if (_periodRec < 0.0f)
			{				
				Bullet* bullet = _tank->Attack();
				bullet->setPosition(GameMain::GetInstance()->convertToNodeSpace(_tank->AttackPoint()));//conver vector space
				GameMain::GetInstance()->addChild(bullet);
				_periodRec = _attackPeriod;
			}		
		}
		else
		{
			_periodRec = 0.0f;
		}
	}
}

void TankControler::SetTank(Tank* tank)
{
	if (_tank)
	{
		_tank->release();
	}
	if (tank)
	{
		_tank = tank;
		_tank->retain();
	}
}

void TankControler::Enable(void)
{
	_keyboardListener->setEnabled(true);
}

void TankControler::Disable(void)
{
	_keyboardListener->setEnabled(false);
	_direction = Vec2::ZERO;
	_attack = false;
}

void TankControler::OnKeyPressed(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event)
{
	switch (key)
	{
	case EventKeyboard::KeyCode::KEY_W:		_direction.add(Vec2(0.0f, 1.0f));	break;
	case EventKeyboard::KeyCode::KEY_S:		_direction.add(Vec2(0.0f, -1.0f));	break;
	case EventKeyboard::KeyCode::KEY_A:		_direction.add(Vec2(-1.0f, 0.0f));	break;
	case EventKeyboard::KeyCode::KEY_D:		_direction.add(Vec2(1.0f, 0.0f));	break;
	case EventKeyboard::KeyCode::KEY_ENTER:	_attack = true;						break;
	case EventKeyboard::KeyCode::KEY_C:
		if (_tank)
		{
			_tank->ChangeColor();
		}
	default:
		break;
	}
}

void TankControler::OnKeyReleased(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event)
{
	switch (key)
	{
	case EventKeyboard::KeyCode::KEY_W:		_direction.add(Vec2(0.0f, -1.0f));	break;
	case EventKeyboard::KeyCode::KEY_S:		_direction.add(Vec2(0.0f, 1.0f));	break;
	case EventKeyboard::KeyCode::KEY_A:		_direction.add(Vec2(1.0f, 0.0f));	break;
	case EventKeyboard::KeyCode::KEY_D:		_direction.add(Vec2(-1.0f, 0.0f));	break;
	case EventKeyboard::KeyCode::KEY_ENTER:	_attack = false;					break;
	default:
		break;
	}
}