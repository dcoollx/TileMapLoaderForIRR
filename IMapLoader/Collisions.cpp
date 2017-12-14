#include "Collisions.h"
namespace MapManager
{
	iCollisions::iCollisions(IMapManager *mapmgr)
	{
		MapMgr = mapmgr;
		if(MapMgr != nullptr)
			gatherSolidPoints();
		//TODO error handle if mapmanger has not been insinuated yet
		
	}
	void iCollisions::gatherSolidPoints()
	{
		auto map = MapMgr->getMap();
		for (int y = 0; y <= map.size(); y++)
		{
			for (int x = 0; x <= map[y].size(); x++)
			{
				if (map[y][x].isSolid)
				{
					solidPoints[map[y][x].identity] = map[y][x].Position;
				}
			}
		}	
	}
	std::map<int, position2d<s32>> iCollisions::testPoximity(cTile player)
	{
		std::map<int, position2d<s32>> closePoints;
		for (int x = 0; x <= MapMgr->clientMap.size(); x++)
		{
			if (solidPoints.count(x))
			{
				if (mainBBox.isPointInside(solidPoints[x]))
				{
					closePoints[x] = solidPoints[x];
				}
			}
		}
		return closePoints;
	}
	void iCollisions::addSolidTiles(cTile ctile)
	{
		solidPoints[ctile.identity] = ctile.Position;
	}

	void iCollisions::setBoundingBox(cTile * tile)
	{
		auto position = tile->Position;
		position2d<s32> newPosition((position.X - tile->width/ 2), (position.Y - tile->height / 2));
		dimension2d<s32> dim(tile->width * 2, tile->height * 2);
		rect<s32> bbox(newPosition, dim);
		mainBBox = bbox;
	}


}

