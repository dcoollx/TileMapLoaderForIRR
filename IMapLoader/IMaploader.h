#pragma once
#include "IMaploader.h"
#include "irrlicht.h"
#include <vector>
#include <map>

using namespace irr;
using namespace irr::core;
using namespace irr::video;
 namespace MapManager
{
	 //Typedef--------------------------------------
	 //typedef std::vector<std::vector<cTile>> mapContainer;

	 //End Typedef---------------------------------
	class IMapManager
	{
		friend class cTile;
		friend class NPC1;
		friend class playableChar;
		friend class iCollisions;
	public:
		rect<s32> mapBound;
		ITexture* sourceImage = NULL;
		position2d<s32> mapOffset; //keeps track of the offset for the map as a whole. is only updated when using the addoffset or setoffset()
		IMapManager(int x, int y, IrrlichtDevice* device, IVideoDriver* driver,stringw xml);//contructor must know the number of tiles in the map
		IMapManager(int size, IrrlichtDevice* device, IVideoDriver* driver);//contructor must know the number of tiles in the map
		~IMapManager();
		void setOffSet(position2d<s32> OFFset, std::vector<std::vector<cTile>> &tiles); //snap offset of map
		void addOffSet(position2d<s32> OFFset, std::vector<std::vector<cTile>> &tiles);// a way to increment offset
		void renderMap(std::vector<cTile> maptiles);
		std::vector<std::vector<cTile>> getMap();
		//std::vector<cTile> createTiles();
		int allTiles;// all number of tiles managed by this instance
		cTile * findTile(int identity); // returns a pointer to a ctile based on its identtity
	protected:
		void loadMap(stringw xml);
		std::vector<std::vector<cTile>> clientMap; // location of map subscribing to map manager
		const stringw mapTag = L"map"; // tag unnessecary?
		const stringw tilesetTag = L"tileset";
		const stringw imageTag = L"image";
		const stringw layerTag = L"layer";
		const stringw dataTag = L"data";
		const stringw tileTag = L"tile";
		const stringw orientationTag;
		int tileHeight;
		int tileWidth;
		dimension2d<s32> mapSize;
		dimension2d<u32> tileDim();
		bool orientation = true;
		int layerCount = 0;
		int tilespace_X;// represent X_space inbetween tiles
		int tilespace_Y;//represent Y space inbetween tiles
		rect<u32> sourecRect();//square representing tile to draw from													
		int mapHeight;// measured in tiles
		int mapWidth;//measured in tiles
	    stringw tileSource;// file name of file containing image
		int sourceimgHeight;
		int sourceimgWidth;
		int layernumber = 0;
		std::vector<int> data;// array storing all tile info 
		int increment = 0;//tiles drawn
		stringw lastsection;
		
		//temp irr device
		IVideoDriver* vdr;
		IrrlichtDevice *Irrdevice;

	};

	class cTile
	{
		
		friend IMapManager;
	protected:
		int Gid = -1; // initialized at a negative number because zero is a valid number represent the global id number of tile ie its texture
		bool bDraw = true;//allow the method rendermap() to draw me
		rect<s32> TextureSq;
		int imgIndex_x;// X coordinate of where to draw from
		int imgIndex_y;
		int mapIndex_x;
		int mapIndex_y;//Y coordinate of where to draw to
		int maxSpeed;
		int acceration;
	
	public:
		int height = 0;
		int width = 0;
		rect<s32> collisonBox;
		position2d<s32> Position;
		int identity;
		position2d<s32> speed = position2d<s32>(0,0); // represents vect of movement
		bool isSolid = false;
		position2d<s32> offset;//relative postion TODO change name
		cTile()
		{

		}

		~cTile()
		{

		}
		virtual void animate()// TODO make into virtual function
		{

		}
		void remove() //removes tile
		{
			bDraw=false;
		
		}
		void setMaxSpeed(int max)
		{
			maxSpeed = max;
		
		}
		void setAcceration(int accel)// maybe float?
		{
			acceration = accel;
		}
		void setGid(int gid, IMapManager* mapmgr)
		{
			height = mapmgr->tileHeight;
			width = mapmgr->tileWidth;
			
			
			if (mapmgr->orientation == true)// map is ortho TODO
			{
				mapIndex_y = (identity / mapmgr->mapWidth)*mapmgr->tileHeight;
				mapIndex_x = (identity % mapmgr->mapWidth)*mapmgr->tileWidth;
				imgIndex_x = (gid % (mapmgr->sourceimgWidth / mapmgr->tileWidth)*mapmgr->tileWidth); //TODO: simplify these formulas(gid%(#ofrows) = x
				imgIndex_y = (floorf(gid / (mapmgr->sourceimgWidth / mapmgr->tileWidth)) * (mapmgr->tileHeight));//hardcoded times 2
				position2d<s32> sorposition(imgIndex_x + mapmgr->tilespace_X, imgIndex_y + mapmgr->tilespace_Y); //source position, where to copy image from
				TextureSq = rect<s32>(sorposition, dimension2d<u32>(mapmgr->tileWidth, mapmgr->tileHeight));
				Position = position2d<s32>(mapIndex_x, mapIndex_y);
				
			}
			else // map is iso
			{
				mapIndex_y = (identity / mapmgr->mapWidth)*mapmgr->tileHeight;
				mapIndex_x = (identity % mapmgr->mapWidth)*(mapmgr->tileWidth/2);
				imgIndex_x = (gid % (mapmgr->sourceimgWidth / mapmgr->tileWidth)*mapmgr->tileWidth); //TODO: simplify these formulas(gid%(#ofrows) = x
				imgIndex_y = (floorf(gid / (mapmgr->sourceimgWidth / mapmgr->tileWidth)) * ((mapmgr->tileHeight)*2));//hardcoded times 2
				position2d<s32> sorposition(imgIndex_x + mapmgr->tilespace_X, imgIndex_y + mapmgr->tilespace_Y); //source position, where to copy image from
				TextureSq = rect<s32>(sorposition, dimension2d<u32>(mapmgr->tileWidth, (mapmgr->tileHeight)*2)); 
				int isoMapIndex_X = mapIndex_x - mapIndex_y;
				int isoMapIndex_Y = (mapIndex_x + mapIndex_y )/ 2;
				Position = position2d<s32>(isoMapIndex_X, isoMapIndex_Y);
				 
				
			}

			Gid = gid;
		}
		int cTile::getGid()
		{
			return Gid;
		}
		void setSolid(bool state)
		{
			isSolid = state;

		}
		virtual void draw(IVideoDriver* vdr, ITexture * sourceImage)//params source image
		{
			if (bDraw)
			{
				vdr->draw2DImage(sourceImage, (Position + offset), TextureSq, 0, SColor(255, 255, 255, 255), true);
				collisonBox = rect<s32>((Position + offset), dimension2d<s32>(width, height));
			}
		}
		 void draw(IVideoDriver* vdr, ITexture * sourceImage, SColor color)//params source image
		{
			if (bDraw)
			{
				vdr->draw2DImage(sourceImage, (Position + offset), TextureSq, 0, color, true);
				collisonBox = rect<s32>((Position + offset), dimension2d<s32>(width, height));
			}

		}
		void draw(IVideoDriver* vdr, ITexture * sourceImage, SColor color, bool Alpha)//params source image
		{
			if (bDraw)
			{
				vdr->draw2DImage(sourceImage, (Position + offset), TextureSq, 0, color, Alpha);
				collisonBox = rect<s32>((Position + offset), dimension2d<s32>(width, height));
			}
			else
			{
				//throw exception

			}
		}

	};
}
