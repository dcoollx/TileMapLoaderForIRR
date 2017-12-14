#pragma once
#include "IKeyboardManager.h"
#include "IMaploader.h" 

namespace MapManager
{
	
	class IKeyboardManager :public IEventReceiver
	{
		friend class playableChar;
		bool KeyIsDown[KEY_KEY_CODES_COUNT];
	public:
		enum eControlscheme
		{
			WSAD = 1,//using the w,s,a,d keyboard buttons
			UDLR,    // using the arrows
			PNCLICK	 // using the mouse(not implemented)
		
		};
		bool OnEvent(const SEvent &event) override
		{
			if (event.EventType == EET_KEY_INPUT_EVENT)
				KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
				return false;


		}
		IKeyboardManager();
		~IKeyboardManager();
		bool isKeyDown(EKEY_CODE keycode);//check keys state
	};
}

