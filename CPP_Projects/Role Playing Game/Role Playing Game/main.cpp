#include "RPG_Engine.h"


int main() {
	RPG_Engine game;
	game.ConstructConsole(256, 240, 4, 4);
	game.Start();

	return 0;
}