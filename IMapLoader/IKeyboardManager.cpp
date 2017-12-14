#include "IKeyboardManager.h"
namespace MapManager
{
	IKeyboardManager::IKeyboardManager()
	{
		for (int i = 0; i < KEY_KEY_CODES_COUNT; i++)
		{
			KeyIsDown[i] = false;



		}
	}
	bool IKeyboardManager::isKeyDown(EKEY_CODE keycode)
	{
		return KeyIsDown[keycode];
	
	}

	IKeyboardManager::~IKeyboardManager()
	{
	}

}
