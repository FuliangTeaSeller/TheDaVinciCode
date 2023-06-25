#pragma once
#include<vector>
#include"Deck.h"
#include"Player.h"
#include"config.h"
#include<cstdlib>
#include<easyx.h>
class Game
{
public:
	Game();
	//~Game();
	void run();
	void init();
	void end();
	bool isGameOver;
private:
	Deck* deck;
	std::vector<Player*>playerlist;
};

