#pragma once
#include<set>
#include"Card.h"
#include"Deck.h"
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include"SearchResult.h"
class Player
{
public:
	//virtual ~Player();
	Player(Deck* deck, const std::string playerName);

	//virtual void play() = 0;
	void addCard(Card card);
	virtual Card* choseCard() = 0;
	virtual std::pair<int, int> guess(Player* target) = 0;
	void drawCard(bool showAllInfo, bool hideWrongAnswer);
	Deck* deck;
	std::vector<Card>hand;
	Card latestCard;
	std::string name;
	bool choseColorFlag;
private:
};
class manPlayer :public Player
{
public:
	Card* choseCard();
	//void play();
	manPlayer(Deck* deck,std::string name);
	std::pair<int, int> guess(Player* target);//second «number
};
class aiPlayer :public Player {
public:
	aiPlayer(Deck* deck, std::string name);
	Card* choseCard();
	std::pair<int, int> guess(Player* target);
private:
	void generateAllSequence(int l, int r,std::vector<Card>& other, std::vector<SearchResult>&result);
	void dfs(int l, int r, std::vector<Card>& other, std::vector<SearchResult>&result,std::vector<int>&tmp);

	void generateAllGuesses(int startIdx, int endIdx, std::vector<Card>& otherHand, std::vector<SearchResult>& results);
	void calculateGuess(int startIdx, int endIdx, std::vector<Card>& otherHand, std::vector<SearchResult>& results, std::vector<int>& currentGuess);
	bool isValidGuess(int value, int idx, std::vector<Card>& hand, std::vector<Card>& otherHand, std::vector<int>& currentGuess);
	void updateGuessCount(int d, std::vector<int>& currentGuess, std::vector<SearchResult>& results);
	void checkResults(std::vector<SearchResult>& results, std::vector<Card>& otherHand);
};

