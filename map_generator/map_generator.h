#pragma once

#include <vector>
#include "../configure.h"

class FenceCombinationFactory
{
public:
	FenceCombinationFactory(void);
	~FenceCombinationFactory(void);

	std::vector<std::vector<Configure::MAP_OBJECT>> CreateRow(void);
	std::vector<std::vector<Configure::MAP_OBJECT>> CreateCol(void);
	std::vector<std::vector<Configure::MAP_OBJECT>> CreateCurve(void);
protected:
	uint8_t	_mapWidth;
	uint8_t	_mapHeight;
};

class MapGenerator
{
public:
	MapGenerator(void);
	~MapGenerator(void);

	std::vector<std::vector<Configure::MAP_OBJECT>> CreateMap(void);

protected:
	void FillLine(void);
	void FillCurve(void);

	FenceCombinationFactory _fenceCombinationFactory;
	std::vector<std::vector<Configure::MAP_OBJECT>> _map;
	uint8_t	_mapWidth;
	uint8_t	_mapHeight;
};