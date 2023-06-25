#include "Game.h"

Game::Game():isGameOver(false)
{
	deck = new Deck();
	playerlist.resize(MAX_PLAYERS);
	Player* p1 = new manPlayer(deck, "manPlayer");
	Player* p2 = new aiPlayer(deck, "aiPlayer");
	playerlist[0] = p1;
	playerlist[1] = p2;
}

void Game::run()
{
	while (!isGameOver) {
		for (int i = 0;i < playerlist.size();i++) {
			std::cout << "\n";
			std::cout << "现在是玩家" << i + 1 << ' ' << playerlist[i]->name << "的回合\n";
			
			Card* chosed = nullptr;
			if (deck->isEmpty()) {
				std::cout << "没有牌了\n";
			}
			else {
				chosed = playerlist[i]->choseCard();
			}
			if (chosed != nullptr) {
				playerlist[i]->latestCard=*chosed;
			}

			while (true)
			{
				auto guess = playerlist[i]->guess(playerlist[!i]);
				Card& guessCard = playerlist[!i]->hand[guess.first];
				std::cout << playerlist[i]->name<<"的猜测是：" << guess.second << guessCard.stringColor() << std::endl;
				guessCard.guessList.insert(guess.second*2+guessCard.getcolor());
				if (guessCard.getnumber() == guess.second) {
					std::cout << "猜对了，接着猜\n";
					guessCard.setswiched(true);

					//检查是否全部猜完
					bool allGuessed=true;
					for (auto i : playerlist[!i]->hand) {
						if (i.getswiched() == false) {
							allGuessed = false;
						}
					}
					if (allGuessed) {
						isGameOver = true;
						std::cout << playerlist[!i]->name << "的牌已经全部猜完了\n";
						goto loopEnd;
					}

					continue;
				}
				else {
					std::cout << "猜错了\n";
					if (chosed!=nullptr){
						playerlist[i]->addCard(playerlist[i]->latestCard);
					}
					playerlist[!i]->drawCard(false,true);
					break;
				}
			}
		}
	loopEnd:
		;
	}
}

void Game::init()
{
	//选手牌
	for (int i = 0;i < playerlist.size();i++) {
		while (playerlist[i]->hand.size() < 4) {
			Card* tmpcard = playerlist[i]->choseCard();
			playerlist[i]->addCard(*tmpcard);
		}
	}

}

void Game::end()
{
	std::cout<<"游戏结束\n";
	for (int i = 0;i < playerlist.size();i++) {
		std::cout << "玩家" << i + 1 << ' ' << playerlist[i]->name << "的手牌\n";
		playerlist[i]->drawCard(true,true);
	}
	std::cout<<"按任意键重开\n";
	system("pause");
	system("cls");
}
