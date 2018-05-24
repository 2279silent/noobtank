#include "cocos2d.h"
#include "map_generator.h"

USING_NS_CC;

FenceCombinationFactory::FenceCombinationFactory(void)
{
	Size&& visibleSize = Director::getInstance()->getVisibleSize();

	_mapWidth = visibleSize.width / Configure::g_baseWidth;
	_mapHeight = visibleSize.height / Configure::g_baseHeight;
}
FenceCombinationFactory::~FenceCombinationFactory(void)
{

}

std::vector<std::vector<Configure::MAP_OBJECT>> FenceCombinationFactory::CreateRow(void)
{
	std::vector<std::vector<Configure::MAP_OBJECT>> fenceMap;
	fenceMap.resize(1);
	fenceMap.at(0).resize(random(3, 2 * _mapWidth / 3), Configure::MAP_OBJECT::FENCE);

	return fenceMap;
}

std::vector<std::vector<Configure::MAP_OBJECT>> FenceCombinationFactory::CreateCol(void)
{
	std::vector<std::vector<Configure::MAP_OBJECT>> fenceMap;
	fenceMap.resize(random(_mapHeight / 3, 2 * _mapHeight / 3), std::vector<Configure::MAP_OBJECT>(1, Configure::MAP_OBJECT::FENCE));
	return fenceMap;
}

std::vector<std::vector<Configure::MAP_OBJECT>> FenceCombinationFactory::CreateCurve(void)
{
	//create map
	std::vector<std::vector<Configure::MAP_OBJECT>> fenceMap;
	uint32_t colSize = random(3, _mapWidth / 2);
	fenceMap.resize(random(3, _mapHeight / 2), std::vector<Configure::MAP_OBJECT>(1, Configure::MAP_OBJECT::GROUND));
	for (auto& row : fenceMap)
	{
		row.resize(colSize, Configure::MAP_OBJECT::GROUND);
	}

	//fill curve
	uint8_t row = 0;
	uint8_t col = 0;
	bool done = false;
	while (done == false)
	{
		//fill fence
		fenceMap.at(row).at(col) = Configure::MAP_OBJECT::FENCE;//left
		fenceMap.at(row).at(fenceMap.at(0).size() - 1 - col) = Configure::MAP_OBJECT::FENCE;//right

		if ((col + 1) >= (fenceMap.at(0).size() - col - 1))
		{
			done = true;
		}
		else
		{
			//check width
			if (col < fenceMap.at(0).size() / 2)//half of width
			{
				col++;
			}
			if (row + 1 < fenceMap.size())
			{
				row++;
			}
		}
	}
	return fenceMap;
}

MapGenerator::MapGenerator(void)
{
	Size&& visibleSize = Director::getInstance()->getVisibleSize();

	_mapWidth = visibleSize.width / Configure::g_baseWidth;
	_mapHeight = visibleSize.height / Configure::g_baseHeight;
}

MapGenerator::~MapGenerator()
{
}

std::vector<std::vector<Configure::MAP_OBJECT>> MapGenerator::CreateMap(void)
{
	_map.resize(_mapHeight, std::vector<Configure::MAP_OBJECT>(1, Configure::MAP_OBJECT::GROUND));
	for (auto& row : _map)
	{
		row.resize(_mapWidth, Configure::MAP_OBJECT::GROUND);
	}

	uint32_t type = random(0, 1);
	std::vector<std::vector<Configure::MAP_OBJECT>> fenceMap;
	switch (type)
	{
	case 0:	FillCurve();		break;
	case 1:	FillCurve();	break;
	default:		break;
	}

	return _map;
}

void MapGenerator::FillLine(void)
{
	if (random(0, 1) == 0)
	{
		//fill a column line
		std::vector<std::vector<Configure::MAP_OBJECT>>&& fenceMap = _fenceCombinationFactory.CreateCol();
		uint32_t fenceStartRow = random((uint32_t)1, _map.size() - fenceMap.size() - 2);
		uint32_t fenceStartCol = random((uint32_t)1, _map.at(0).size() - 2);
		for (auto& row : fenceMap)
		{
			for (auto& col : row)
			{
				_map.at(fenceStartRow).at(fenceStartCol) = col;
			}
			fenceStartRow++;
		}
	}
	else
	{
		std::vector<std::vector<Configure::MAP_OBJECT>>&& fenceMap = _fenceCombinationFactory.CreateRow();
		uint32_t fenceStartRow = random((uint32_t)1, _map.size() - 2);
		uint32_t fenceStartCol = random((uint32_t)1, _map.at(0).size() - fenceMap.at(0).size() - 2);
		for (auto& row : fenceMap)
		{
			for (auto& col : row)
			{
				_map.at(fenceStartRow).at(fenceStartCol) = col;
				fenceStartCol++;
			}
		}
	}
}

void MapGenerator::FillCurve(void)
{
	std::vector<std::vector<Configure::MAP_OBJECT>>&& fenceMap = _fenceCombinationFactory.CreateCurve();
	uint32_t fenceStartRow = random((uint32_t)1, _map.size() - fenceMap.size() - 2);
	uint32_t fenceStartCol = random((uint32_t)1, _map.at(0).size() - fenceMap.at(0).size() - 2);
	for (auto& row : fenceMap)
	{
		int startCol = fenceStartCol;
		for (auto& col : row)
		{
			_map.at(fenceStartRow).at(startCol) = col;
			startCol++;
		}
		fenceStartRow++;
	}
}