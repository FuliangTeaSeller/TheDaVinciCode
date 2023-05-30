#include "Game.h"

Game::Game()
{
	deck = new Deck();
	playerlist.resize(MAX_PLAYERS);
	Player* p1 = new manPlayer(deck);
	Player* p2 = new aiPlayer(deck);
	playerlist[0] = p1;
	playerlist[1] = p2;
}

void Game::run()
{
	//while (!(deck->cardsToDealt[0].empty())&& !(deck->cardsToDealt[1].empty()))
	for (int i = 0;i < playerlist.size();i++) {
		std::cout << "���������" << i << "�Ļغ�\n";
		playerlist[i]->play();
	}
}

void Game::init()
{
	//ѡ����
	for (int i = 0;i < playerlist.size();i++) {
		while (playerlist[i]->hand.size() < 4) {
			Card* tmpcard = playerlist[i]->choseCard();
			playerlist[i]->addCard(*tmpcard);
		}
	}

}
