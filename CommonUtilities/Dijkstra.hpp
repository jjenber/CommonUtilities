#pragma once
#include <vector>

namespace CommonUtilities
{
	static const int MapWidth; 
	static const int MapHeight;
	static const int TileCount = MapWidth * MapHeight;

	enum class Tile
	{
		Impassable,
		Passable
	};

	std::vector<int> Dijkstra(const std::vector<Tile>& aMap, int aStartIndex, int anEndIndex)
	{

	}
}
