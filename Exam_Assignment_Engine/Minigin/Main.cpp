#include "MiniginPCH.h"
#include <vld.h>
#include "Minigin.h"
#include "../DigDug/Game.h"


#pragma warning( push )  
#pragma warning( disable : 4100 )  
int main(int argc, char* argv[]) 
{
	#pragma warning( pop )
	//_CrtSetBreakAlloc(5226);
	Game game;
	dae::Minigin engine;
	engine.Initialize();
	game.SetupGame();
	engine.Run();
	//_CrtDumpMemoryLeaks();
    return 0;
}

