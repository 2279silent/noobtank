#pragma once

#include <cstdint>
#include <string>

namespace Configure
{
	const float g_baseWidth = 64.0f;

	const float g_baseHeight = 64.0f;

	enum class MAP_OBJECT :uint8_t
	{
		GROUND=0,
		HAY,
		FENCE,
		BULLET,
		TANK,
	};

	enum class BULLET_DAMAGE :uint8_t
	{
		RED = 10,
		BLUE = 20,
		GREEN = 25,
	};

	enum class Health :uint8_t
	{
		BASIC = 100,
	};

	enum class TANKCOLOR :uint8_t
	{
		RED = 0,
		GREEN,
		BLUE,
	};

	class TankInfo
	{
	public:
		static std::string Name(TANKCOLOR color)
		{
			switch (color)	
			{
			case Configure::TANKCOLOR::RED:		return "tank_red";		break;
			case Configure::TANKCOLOR::GREEN:	return "tank_green";	break;
			case Configure::TANKCOLOR::BLUE:	return "tank_blue";		break;
			default:							return "";				break;
			}
		}
		static uint8_t Damage(TANKCOLOR color)
		{
			switch (color)
			{
			case Configure::TANKCOLOR::RED:		return static_cast<uint8_t>(BULLET_DAMAGE::RED);		break;
			case Configure::TANKCOLOR::GREEN:	return static_cast<uint8_t>(BULLET_DAMAGE::GREEN);		break;
			case Configure::TANKCOLOR::BLUE:	return static_cast<uint8_t>(BULLET_DAMAGE::BLUE);		break;
			default:							return 0;												break;
			}
		}
	};
}