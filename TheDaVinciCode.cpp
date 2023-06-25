#include"Game.h"
int main()
{
	while (true) {
		Game game;
		game.init();
		game.run();
		game.end();
	}
	return 0;
}