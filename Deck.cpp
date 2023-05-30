#include "Deck.h"

Deck::Deck()
{
	deck.resize((MAX_CARD_NUM + JOCKER) * 2);
	for (int i=0;i<deck.size();i++)
	{
		deck[i]=Card(i);
	}
	if (JOCKER)
	{
		deck[deck.size()-1]=Card(-2);
		deck[deck.size()-2]=Card(-3);
	}
	shuffleSequence();
	for (int i=0;i<deck.size();i++)
	{
		cardsToDealt[deck[i].getcolor()].push(&deck[i]);
	}
}

void Deck::shuffleSequence()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::shuffle(deck.begin(), deck.end(), gen);
}
