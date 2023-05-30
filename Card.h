#pragma once
#include<string>
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
	cardColor getcolor()const { return color; }
	int getnumber()const { return number; }
	int getvalue()const { return value; }
	Card(int number, cardColor color);
	Card(int value);
	Card() :value(-10) {}
	std::string stringColor();
	//~Card();
	const bool operator<(const Card& card)const;
};

