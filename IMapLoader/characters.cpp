#include "characters.h"
#include "IKeyboardManager.h"

namespace MapManager
{
	playableChar::~playableChar()
	{
	}

	void playableChar::draw()//will only work if registered to a mapmanager
	{
		Mapmanger->vdr->draw2DImage(sprites,Position,rect<s32>(position2d<s32>(),position2d<s32>(32,32)),0,SColor(255,255,255,255),true);
	
	}
	
	playableChar::playableChar(stringw spritesheet,IMapManager *manager,IKeyboardManager::eControlscheme scheme, IKeyboardManager* keyb)//start using a spriteshite
	{
		spriteSheet = manager->vdr->getTexture(spritesheet);
		manager->allTiles++;
		Mapmanger = manager;
		cScheme = scheme;
		bounding = manager->vdr->getViewPort();
		Position = bounding.getCenter();
		KEYb = keyb;
	}

	void playableChar::animate(state state, ITimer *timer) //return texture??
	{
		if (!animations.empty())
		{
			//u32 now = timer->getTime();
			/*switch (state)
			case walk:
				this->sprites =
					animationDelta = now;*/
		}
		else {
			//
		}
	}

	playableChar::state playableChar::listen(std::vector<std::vector<cTile>> &map)
	{
		//TODO add test for multiple key inputs

			if (cScheme == IKeyboardManager::eControlscheme::WSAD)
			{
				if (KEYb->isKeyDown(KEY_KEY_W))//up
				{
					if(speed<position2d<s32>( maxSpeed, maxSpeed))
					speed = speed + position2d<s32>(0, acceration);
					//TODO check for collision
					//todo animation()
					Mapmanger->addOffSet(speed, map);
					return playableChar::state::walk;
				}
				if (KEYb->isKeyDown(KEY_KEY_S))//down
				{
					//speed = position2d<s32>(0, -acceration);
					Mapmanger->addOffSet(position2d<s32>(0, -2), map);
					//return playableChar::state::walk;
				}
				if (KEYb->isKeyDown(KEY_KEY_A))
				{
					Mapmanger->addOffSet(position2d<s32>(2, 0), map);
					//return playableChar::state::walk;
				}
				if (KEYb->isKeyDown(KEY_KEY_D))
				{
					Mapmanger->addOffSet(position2d<s32>(-2, 0), map);
					//ssssssssreturn playableChar::state::walk;
				}
				else
					speed = position2d<s32>(0,0);// deceleration?


			}
			if (cScheme == IKeyboardManager::eControlscheme::UDLR)//arrow keys
			{
				if (KEYb->isKeyDown(KEY_UP))//up
				{
					Mapmanger->addOffSet(position2d<s32>(0, 2), map);
					return playableChar::state::walk;
				}
				if (KEYb->isKeyDown(KEY_DOWN))//down
				{
					Mapmanger->addOffSet(position2d<s32>(0, -2), map);
					return playableChar::state::walk;
				}
				if (KEYb->isKeyDown(KEY_LEFT))
				{
					Mapmanger->addOffSet(position2d<s32>(2, 0), map);
					return playableChar::state::walk;
				}
				if (KEYb->isKeyDown(KEY_RIGHT))
				{
					Mapmanger->addOffSet(position2d<s32>(-2, 0), map);
					return playableChar::state::walk;
				}

			}
			if (cScheme == IKeyboardManager::eControlscheme::PNCLICK)
			{
				//not implemented
			}
			else
				return playableChar::state::idle;
		}
	
}