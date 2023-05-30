#include "Card.h"

Card::Card(int number, cardColor color):number(number),color(color)
{
	value = number * 2 + color;
}

Card::Card(int value):value(value)
{
	number = value / 2;
	color = (cardColor)(value % 2);
}

std::string Card::stringColor()
{
	std::string ret;
	if (color == BLACK)ret = "B";
	else if (color == WHITE)ret = "W";
	return ret;
}



const bool Card::operator<(const Card& card) const
{
	if (this->value < 0)return true;
	return this->value < card.value;
}
