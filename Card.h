#pragma once
#include<string>
#include <functional>
#include<set>
enum cardColor
{
	BLACK, WHITE
};
class Card
{
private:
	int number;
	int value;
	cardColor color;
	bool swiched = false;
public:
	std::set<int> guessList;
	cardColor getcolor()const { return color; }
	int getnumber()const { return number; }
	int getvalue()const { return value; }
	bool getswiched()const { return swiched; }
	void setswiched(bool flag) { swiched = flag; }
	Card(int number, cardColor color);
	Card(int value);
	//Card() = default;
	std::string stringColor()const;
	const bool operator<(const Card& card)const;
	const bool operator==(const Card& card)const;
};

