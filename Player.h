#pragma once
#include<set>
#include"Card.h"
#include"Deck.h"
#include<iostream>
#include<string>
class Player
{
public:
	//virtual ~Player();
	Player(Deck* deck);

	virtual void play() = 0;
	void addCard(Card card);
	virtual Card* choseCard() = 0;
	virtual void guess() = 0;
	Deck* deck;
	std::set<Card>hand;
	Card latestCard;
	std::string name;
	bool choseColorFlag;
private:
};
class manPlayer :public Player
{
public:
	//manPlayer();
	Card* choseCard();
	void play();
};
class aiPlayer :public Player {
public:
	//aiPlayer(Deck* deck);
	Card* choseCard();
	void play();
};

