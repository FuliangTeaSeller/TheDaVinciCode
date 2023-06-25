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
			std::cout << "���������" << i + 1 << ' ' << playerlist[i]->name << "�Ļغ�\n";
			
			Card* chosed = nullptr;
			if (deck->isEmpty()) {
				std::cout << "û������\n";
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
				std::cout << playerlist[i]->name<<"�Ĳ²��ǣ�" << guess.second << guessCard.stringColor() << std::endl;
				guessCard.guessList.insert(guess.second*2+guessCard.getcolor());
				if (guessCard.getnumber() == guess.second) {
					std::cout << "�¶��ˣ����Ų�\n";
					guessCard.setswiched(true);

					//����Ƿ�ȫ������
					bool allGuessed=true;
					for (auto i : playerlist[!i]->hand) {
						if (i.getswiched() == false) {
							allGuessed = false;
						}
					}
					if (allGuessed) {
						isGameOver = true;
						std::cout << playerlist[!i]->name << "�����Ѿ�ȫ��������\n";
						goto loopEnd;
					}

					continue;
				}
				else {
					std::cout << "�´���\n";
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
	//ѡ����
	for (int i = 0;i < playerlist.size();i++) {
		while (playerlist[i]->hand.size() < 4) {
			Card* tmpcard = playerlist[i]->choseCard();
			playerlist[i]->addCard(*tmpcard);
		}
	}

}

void Game::end()
{
	std::cout<<"��Ϸ����\n";
	for (int i = 0;i < playerlist.size();i++) {
		std::cout << "���" << i + 1 << ' ' << playerlist[i]->name << "������\n";
		playerlist[i]->drawCard(true,true);
	}
	std::cout<<"��������ؿ�\n";
	system("pause");
	system("cls");
}
