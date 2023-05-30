#include "Player.h"

Card* aiPlayer::choseCard()
{
	choseColorFlag = !choseColorFlag;
	Card* ret = (*deck).cardsToDealt[choseColorFlag].front();
	(*deck).cardsToDealt[choseColorFlag].pop();
	return ret;
}

Player::Player(Deck* deck) :deck(deck), latestCard(-10)
{
}

void Player::addCard(Card card)
{
	if (card.getvalue() != -10) {
		hand.insert(card);
	}
}



Card* manPlayer::choseCard()
{
	Card* ret = nullptr;
	std::cout << "选一个颜色b/w,或者随机a\n";
	std::cout << "当前牌堆数目\n黑:" << deck->cardsToDealt[BLACK].size() << " 白：" << deck->cardsToDealt[WHITE].size() << std::endl;
	char ch;
	cardColor tmpflag;
	while (true) {
		std::cin >> ch;
		ch = tolower(ch);
		if (ch == 'a' || ch == 'b' || ch == 'w')
		{
			if (ch == 'a') {
				tmpflag = (cardColor)choseColorFlag;
				if ((*deck).cardsToDealt[tmpflag].empty()) {
					tmpflag = (cardColor)(!choseColorFlag);
				}
			}
			else if (ch == 'b') {
				tmpflag = BLACK;
			}
			else if (ch == 'w') {
				tmpflag = WHITE;
			}
		}
		if ((*deck).cardsToDealt[tmpflag].empty()) {
		std:cout << "这个颜色的牌已经没有了，请重新选择\n";
		}
		else {
			break;
		}
	}
	ret = (*deck).cardsToDealt[tmpflag].front();
	(*deck).cardsToDealt[tmpflag].pop();
	std::cout << "选到的牌是：" << ret->getnumber() << ret->stringColor() << std::endl;
	return ret;
}

void manPlayer::play()
{

}
