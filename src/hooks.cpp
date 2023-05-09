#include "hooks.h"
#include "menu.h"
#include "gamedata/gamedata.h"
#include <cstdint>


extern WTHack_vars gVars;

HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (!gVars.menu->isInitialized())
		gVars.menu->init(pSwapChain);
	

	if(gVars.menu->draw)
		gVars.menu->drawMenu();

	gVars.game->update();

	return gVars.oPresent(pSwapChain, SyncInterval, Flags);
}