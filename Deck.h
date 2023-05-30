#pragma once
#include<vector>
#include"Card.h"
#include"config.h"
#include<random>
#include"Card.h"
#include<queue>
class Deck
{
public:
	std::vector<Card>deck;
	std::vector<std::queue<Card*>>cardsToDealt;
	Deck();
private:
	void shuffleSequence();
};

