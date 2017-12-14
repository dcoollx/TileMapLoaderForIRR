#include "IMaploader.h"

using namespace irr;
using namespace irr::core;
using namespace irr::io;
using namespace irr::scene;
using namespace irr::video;
using namespace MapManager;

namespace MapManager
{
	cTile *IMapManager::findTile(int identity)
	{
		for (int x = 0; x <= clientMap.size(); x++)
		{
			for (int y = 0; y <= clientMap[x].size(); x++)
			{
				if (clientMap[x][y].identity == identity)
					return &clientMap[x][y];
			}
		}
	}
	IMapManager::IMapManager(int x, int y, IrrlichtDevice* device, IVideoDriver* driver,stringw xml)
	{
		mapSize = dimension2d<s32>(x,y);
		data.resize(mapSize.getArea());
		Irrdevice = device;
		vdr = driver;
		loadMap(xml);
	}
	IMapManager::~IMapManager()
	{
	}
	void IMapManager::addOffSet(position2d<s32> OFFset, std::vector<std::vector<cTile>> &tiles)
	{
		position2d<s32> finalOffset;
		finalOffset = mapOffset + OFFset;
		for (int i = 0; i < tiles.size(); i++)
		{
			for (int c = 0; c < tiles[i].size(); c++)
			{
				tiles[i][c].offset = finalOffset;
			}
		}
		mapOffset = finalOffset;
	}

	void IMapManager::setOffSet(position2d<s32> OFFset, std::vector<std::vector<cTile>> &tiles)
	{
		
		for (int i = 0; i < tiles.size(); i++)
		{
			for (int c = 0; c < tiles[i].size(); c++)
			{
				tiles[i][c].offset =OFFset;
			}
		}

		mapOffset = OFFset;
	}

	/*std::vector<cTile> IMapManager::createTiles()// must call loadmap() first
	{

	if (data[1]!=-1)
	{

	std::vector<cTile> tiles(mapSize);
	for (int i = 0; i < mapSize; i++)
	{
	tiles[i].identity = i ;
	tiles[i].setGid(data[i], this);
	}
	allTiles += mapSize;
	return tiles;
	}
	else
	{
	//return NULL;
	}

	}//works*/

	void IMapManager::renderMap(std::vector<cTile> maptiles)
	{
		//if(tiles!=NULL)
		for (int c = 0; c< mapSize.getArea(); c++)//draws map backwards
		{
			maptiles[c].draw(vdr, sourceImage);

		}


	}

	std::vector<std::vector<cTile>>IMapManager::getMap()
	{
		return clientMap;
	}

	void IMapManager::loadMap(stringw xml)
	{
		std::vector<std::vector<cTile>> tempmap;
		io::IXMLReader *xmlRder = Irrdevice->getFileSystem()->createXMLReader(xml);//loades map file into memory
		//if (!xmlRder)
		//return 0;TODO error handling

		while (xmlRder->read())
		{

			switch (xmlRder->getNodeType())
			{
			case irr::io::EXN_ELEMENT:
			{

				if (mapTag.equals_ignore_case(xmlRder->getNodeName())) // if we havent started and we found the first node
				{
					lastsection = mapTag; //now working on map
					if (xmlRder->getAttributeValueSafe(L"orientation") == L"orthogonal")
						orientation = true;
					else if (xmlRder->getAttributeValueSafe(L"orientation") == L"isometric")
						orientation = false;
					else
						orientation = true;//if not specified default to ortho
					tileHeight = xmlRder->getAttributeValueAsInt(L"tileheight");
					tileWidth = xmlRder->getAttributeValueAsInt(L"tilewidth");
					mapHeight = xmlRder->getAttributeValueAsInt(L"height");
					mapWidth = xmlRder->getAttributeValueAsInt(L"width");
					mapBound = rect<s32>(0, 0, (mapSize.Width *tileWidth), (mapSize.Height*tileHeight));
					
					//font->draw(L"in map tag", rect<s32>(), SColor(255, 0, 0, 0), false, false, NULL);
				}
				else if (tilesetTag.equals_ignore_case(xmlRder->getNodeName()))//in tileset tag
				{
					lastsection = tilesetTag;
					tilespace_X = xmlRder->getAttributeValueAsInt(L"spacing");
					tilespace_Y = xmlRder->getAttributeValueAsInt(L"margin");
				}
				else if (imageTag.equals_ignore_case(xmlRder->getNodeName()))
				{
					sourceimgHeight = xmlRder->getAttributeValueAsInt(L"height");
					sourceimgWidth = xmlRder->getAttributeValueAsInt(L"width");
					tileSource = xmlRder->getAttributeValueSafe(L"source");
					// tileSource = "C:/Users/David/Documents/Visual Studio 2013/Projects/IMapLoader/IMapLoader/Debug/Assets/desertTileset.png";
					sourceImage = vdr->getTexture(io::path(tileSource));
				}
				else if (layerTag.equals_ignore_case(xmlRder->getNodeName()))//reached a layer element increment to keep track of the numbers of layers
				{
					layerCount++;
					tempmap.resize(layerCount);
				}
				else if (dataTag.equals_ignore_case(xmlRder->getNodeName()))// data node
				{/* this is the meat of this function it will use the data here to render the stage*/

				}
				else if (tileTag.equals_ignore_case(xmlRder->getNodeName()))
				{
					if (xmlRder->getAttributeValueAsInt(L"gid") >= 0)// prevents reading of trash data
					{
						data[increment] = xmlRder->getAttributeValueAsInt(L"gid") - 1; // works
						if (increment < mapSize.getArea())
						{
							increment++;
						}
					}

				}

			}

			break;
			case irr::io::EXN_ELEMENT_END: //reached the end of an element in most cases just break
			{
				if (layerTag.equals_ignore_case(xmlRder->getNodeName())) //end of layer tag
				{
					for (int i = 0; i < layerCount; i++)
					{
						tempmap[i].resize(mapSize.getArea());
					}

					for (int i = 0; i < mapSize.getArea(); i++)
					{
						tempmap[layerCount - 1][i].identity = i;//+(layercount * mapsize)--causes an error?
						tempmap[layerCount - 1][i].setGid(data[i], this);
					}
					allTiles += mapSize.getArea();
					data.empty();
					increment = 0;

				}


			}
			break;

			}
		}
		xmlRder->drop();
		clientMap = tempmap;
		//return tempmap;// no need to return map, anything that needs to use map ccan access it through mapamangger
	}//works
}