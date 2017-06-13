#include "StdUI.h"



int getcharIfKbhit(void);

#ifdef _EG_WINDOWS_PLATFORM
#include <conio.h>
#endif

int getcharIfKbhit(void)
{
	int res = _kbhit();
	if (res)
		res = _getch();
	return res;
}


#if defined _EG_WINDOWS_PLATFORM || defined _EG_XB1_PLATFORM
#	define SLEEP(ms) Sleep(ms)
# endif



StdUI::StdUI(void)
	: mExit(false)
{}

void StdUI::usage(void)
{

	Console::get().writeLine(L"Photon LoadBalancing Demo");
	Console::get().writeLine(L"usage:");
	Console::get().writeLine(L"always:");
	Console::get().writeLine(L" h - print this help");
	Console::get().writeLine(L" 0 - exit");
	Console::get().writeLine(L"--------------------");
	Console::get().writeLine(L"outside a game room:");
	Console::get().writeLine(L" 1 - create game");
	Console::get().writeLine(L" 2 - join random game or last joined game");
	
	Console::get().writeLine(L"--------------------");
	Console::get().writeLine(L"inside a game room:");
	Console::get().writeLine(L" 1 - leave game");
	Console::get().writeLine(L" 2 - leave game (will come back - disconnects and quits)");
	Console::get().writeLine(L" 3 - play");
	Console::get().writeLine(L"--------------------");

}

void StdUI::main(void)
{

	usage();
	getNetworkLogic().connect();
	while (getNetworkLogic().getLastInput() != INPUT_EXIT && !mExit)
		main_loop();
}

void StdUI::main_loop()
{
	int ch = getcharIfKbhit();
	switch (ch)
	{
	case 'h':
		usage();
		break;
	case '0':
		getNetworkLogic().setLastInput(INPUT_EXIT);
		mExit = true;
		break;
	default:
		getNetworkLogic().setLastInput(INPUT_NON);
		break;
	}
	switch (ch)
	{
	case '1':
		getNetworkLogic().setLastInput(INPUT_1);
		break;
	case '2':
		getNetworkLogic().setLastInput(INPUT_2);
		break;
	case '3':
		getNetworkLogic().setLastInput(INPUT_3);
		break;
	}
	getNetworkLogic().run();
	Console::get().update();
	SLEEP(10);
}

NetworkLogic& StdUI::getNetworkLogic(void)
{
	static NetworkLogic networkLogic(&Console::get());
	return networkLogic;
}


