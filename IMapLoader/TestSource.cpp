 #include "IKeyboardManager.h"
#include "IMaploader.h"
#include "irrlicht.h"
#include "characters.h"
#include <memory>
#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#define null 0
#endif

using namespace irr;
using namespace irr::video;
using namespace irr::core;
using namespace irr::io;
using namespace irr::gui;
using namespace irr::scene;


using namespace MapManager; // names space of 2d engine

// just some vars that make that i used alot
SColor Black = SColor(255, 0, 0, 0);			
SColor White = SColor(255, 255, 255, 255);
SColor Gray = SColor(255, 175, 175, 175);
dimension2d<u32> fullscreen(1440, 900);
dimension2d<u32> screen(500, 500);


IKeyboardManager keys; // this class inheretes from IEventReciever to catch keyborad events
//--normal irr device interfaces----------------------------------
IrrlichtDevice *dev = createDevice( EDT_DIRECT3D9, screen,16,false,false,false, &keys);//pass instance of Ikeyboardmanager to recive events
IVideoDriver* vdr = dev->getVideoDriver();
//----------------------------------you only need one instance of mapmger per level
stringw mapURL = "C:/Users/dj/Documents/IMapLoader/IMapLoader/Assets/sewers.tmx";
IMapManager mapmgr(150,150, dev, vdr, mapURL);

std::vector<std::vector<cTile>> Wholemap;// will hold the map. The first dimensions represent the number of layers
MapManager::playableChar player1("Assets/testcharacter.png",&mapmgr, IKeyboardManager::eControlscheme::WSAD, &keys);



int main()
{
	player1.setMaxSpeed(5);
	player1.setAcceration(1);
	dev->setWindowCaption(L"map testing");
	ITimer *timer = dev->getTimer();
	
	if (mapmgr.sourceImage != NULL)//loads map info into mapmanger must be called first before using any other mapmagr calls returns a boolean 
	{
		//Wholemap = mapmgr.loadMap("C:/Users/dj/Documents/IMapLoader/IMapLoader/Assets/sewers.tmx"); this function is called by contructor
		Wholemap = mapmgr.getMap();//new way of getting map
		vdr->makeColorKeyTexture(mapmgr.sourceImage, vector2d<s32>(90,0));	
		while (dev->run())
		{
			u32 then;
			u32 now;
			timer->start();
			now = timer->getTime();
			vdr->beginScene(true,false,Black);//irr begin scene, all drawing happens here-------------
			mapmgr.renderMap(Wholemap[0]);// draws all tiles in mapmanger the first subscript is which layer to draw
			//Wholemap[0][0].remove(); // specif tiles can be addressed like this
			//Wholemap[0][0].draw(vdr, mapmgr.sourceImage);
			player1.draw();// all tile objects have a draw method that can be overriden
			//player2.draw();
			mapmgr.renderMap(Wholemap[1]);/* draw second layer above characters. Using this technique can give a psuedo-3D feel to your game*/
			player1.animate(player1.listen(Wholemap), timer); /* include this line to link player to keyboard. Be sure to call listen at the end of the frame or the 
									  character will move before the scene is re-drawn*/
			//----------------------end drawing calls


			vdr->endScene();
			

		}
	}
	else
		return 1;
	dev->drop();
	
	return 0;
}
