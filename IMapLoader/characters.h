#pragma once
#include "IKeyboardManager.h"
#include "IMaploader.h"
#include "irrlicht.h"
namespace MapManager
{
	class NPC1 :public cTile
	{
protected:
		IMapManager *Mapmanger;//the mapmgr this node reports to
		bool isSolid;
		irr::u32 animationDelta = 0;//used by animation
		std::map<std::string, std::vector<ITexture>> animations;
	public:
		ITexture* spriteSheet;
		ITexture * sprites; // indivual sprite selected during animation
		NPC1(){}
		~NPC1(){}
		NPC1(IMapManager *mapmgr){}
		enum state
		{
			idle,
			walk,
			run,
			hurt,
			die,
		
		};

	};
	class playableChar : public NPC1 /* A class of a single tile linked to the keyboard params stringw spriteshite- location of image that will 
									 be used as the texture manager- a pointer to the active IMapManager class scheme- enumeration representing
									 the way the tile will be linked to the keyboard*/
	{
		bool bDraw =true;// will not be automatically draw by mapmangr
		//TODO add controls
	protected:
		int life;
		int cScheme;
		IKeyboardManager *KEYb;
		
	public:
		~playableChar();
		state listen(std::vector<std::vector<cTile>> &map);
		playableChar(stringw spritesheet, IMapManager* manager,IKeyboardManager::eControlscheme scheme,IKeyboardManager *keysb);//start using a spriteshite
		void draw();
		rect<s32> bounding;
		void animate(state state, ITimer *timer);// Move to NPC??






	};
}