#pragma once
#include "IMaploader.h"
// this class manages the hit test that take place in every frame.
//the goal is to create an accurrate AND effiecent way to reliably test a colission between ANY two object that exisit within the mapmanager interface class
//goal:
//		object1.test(object2)
// how to idenify ob2??
// list of 'close obj!?
// revise ob1.test(closeObjs[x])
namespace MapManager
{
		class iCollisions
		{
		public:
			iCollisions(IMapManager *mapmgr);
			void addSolidTiles(cTile ctile);
			~iCollisions();
			void setBoundingBox(position2d<u32> position);//set box around a certain absolute postion
			void setBoundingBox(cTile *tile);
			

		protected:
			rect<s32> mainBBox;
			IMapManager * MapMgr;
			std::map<int, position2d<s32>> solidPoints;// the origin posistion of all tiles that are solid
			void gatherSolidPoints();
			std::map<int, position2d<s32>> testPoximity(cTile player); // returns a list of tiles close enough to collide;
			std::vector<int> testCollisions(cTile ctile, std::vector<position2d<s32>> closeTiles);
			


		};

}

