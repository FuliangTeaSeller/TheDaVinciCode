#include "Deck.h"

Deck::Deck()
{
	//deck.resize((MAX_CARD_NUM + JOCKER) * 2);
	for (int i=0;i< MAX_CARD_NUM * 2;i++)
	{
		deck.push_back(Card(i));
	}
	if (JOCKER)
	{
		deck.push_back(Card(-2));
		deck.push_back(Card(-3));
	}
	shuffleSequence();
	cardsToDealt.resize(2);
	for (int i=0;i<deck.size();i++)
	{
		cardsToDealt[deck[i].getcolor()].push(&deck[i]);
	}
}

bool Deck::isEmpty()
{
	return cardsToDealt[0].empty() && cardsToDealt[1].empty();
}

void Deck::shuffleSequence()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::shuffle(deck.begin(), deck.end(), gen);
}
