#include "Player.h"

aiPlayer::aiPlayer(Deck* deck, std::string name) :Player(deck, name)
{
}

Card* aiPlayer::choseCard()
{
	choseColorFlag = !choseColorFlag;
	if ((*deck).cardsToDealt[choseColorFlag].empty()) {
		choseColorFlag = !choseColorFlag;
	}
	Card* ret = (*deck).cardsToDealt[choseColorFlag].front();
	(*deck).cardsToDealt[choseColorFlag].pop();
	return ret;
}

//void aiPlayer::play(Player* target)
//{
//}

//std::pair<int, int> aiPlayer::guess(Player* target)
//{
//	std::vector<Card> targetCopy;
//	for (auto i : target->hand) {
//		targetCopy.push_back(i);
//	}
//	/*{
//		bool atLeastOne = false;
//		for (const auto i : tmp) {
//			if (i.getswiched() == true) {
//				atLeastOne = true;
//				break;
//			}
//		}
//		if (atLeastOne == false) {
//			int guessSequence[] = { 12,11,13,10,14,9,15,8,16,7,17,6,18,5,19,4,20,3,21,2,22,1,23,0,24 };
//			int mid = tmp.size() / 2;
//			for (int i : guessSequence) {
//				auto res = std::find(tmp[mid].guessList.begin(), tmp[mid].guessList.end(), i);
//				if (res != tmp[mid].guessList.end()) {
//					tmp[mid].guessList.push_back(i);
//					return std::make_pair(mid, i);
//				}
//			}
//		}
//	}*///��֪�����ڸ�ʲô
//	std::vector<SearchResult>result(targetCopy.size());
//	for (int i = 0;i < result.size();i++) {
//		result[i].idx = i;
//	}
//	generateAllSequence(0, targetCopy.size(), targetCopy, result);
//	for (auto& i : result) {
//		if (targetCopy[i.idx].getswiched() == true) {
//			continue;//����������Ѿ��������ˣ���ô�Ͳ�Ҫ�ٲ���
//		}
//		int total = 0;
//		int maxvalue = -1;
//		int maxvalueIndex = -1;
//		for (int j = 0;j < i.guessList.size();j++) {
//			total+= i.guessList[j];
//			if (maxvalue < i.guessList[j]) {
//				maxvalue = i.guessList[j];
//				maxvalueIndex = j;
//			}
//		}
//		i.bestResult.second = (double)maxvalue / total;
//		i.bestResult.first = maxvalueIndex;
//	}
//	std::sort(result.begin(), result.end());
//	std::cout<<"ai�²�λ��"<<result[0].idx+1<<" ׼ȷ��"<<result[0].bestResult.second<<std::endl;
//	return std::make_pair(result[0].idx, result[0].bestResult.first/2);
//}

void aiPlayer::generateAllSequence(int l, int r, std::vector<Card>& other, std::vector<SearchResult>& result)
{
	//ʹ��dfs�ķ�ʽ����l->r�����ڵ�����������������ɳ��������浽result
	std::vector<int>tmp(r - l);
	dfs(l,r,other,result,tmp);
}

void aiPlayer::dfs(int l, int r, std::vector<Card>& other, std::vector<SearchResult>& result, std::vector<int>& tmp)
{
	if (l == r) {
		for (int i = 0;i < tmp.size();i++) {
			int guessValue = tmp[i];
			int guessIndex = i;
			result[guessIndex].guessList[guessValue]++;
		}
		return;
	}
	//����ö��value�����ų�һЩ����
	for (int value = 0;value < MAX_CARD_NUM * 2;value++) {
		//auto res1 = std::find(other[l].guessList.begin(), other[l].guessList.end(), Card(value));
		bool flag1 = false;
		for (auto& res1 : other[l].guessList) {
			if (res1 == value) {
				flag1 = true;
				break;
			}
		}
		if (flag1) { continue; }//���λ���Ѿ��¹��������

		bool flag2 = false;
		for (auto& res2 : hand) {
			if (res2.getvalue() == value) {
				flag2 = true;
				break;
			}
		}
		if (flag2) { continue; }//�Լ��е��ƾͲ��ò���

		bool flag3 = false;
		for (auto& i : other) {
			if (i.getswiched() == true) {
				if (value == i.getvalue()) {
					flag3 = true;
					break;
				}
			}
		}
		if (flag3) { continue; }//���������ط����³����ˣ�Ϊɶ��Ҫ������ط���������

		if (l >= 1) {
			if(tmp[l-1]>value){continue;}//��֤�µ����ǵ�����
		}

		//��һ���ֿ���value����С����������������Ǹ��Ѿ�swiched���Ƶ�value
		for (int i = l + 1;i < r;i++) {
			if (other[i].getswiched() == true) {
				if (value > other[i].getvalue()) {
					return;//��֦
				}
				break;
			}
		}
		


		//other������ط�����Ѿ�swiched�ˣ���ô����ط����ƾ���ȷ���ģ����ò���
		if (other[l].getswiched() == true) {
			tmp[l] = other[l].getvalue();
		}
		else {
			tmp[l] = value;
		}

		dfs(l + 1, r, other, result, tmp);
	}
}

Player::Player(Deck* deck, const std::string playerName) :deck(deck), latestCard(LATEST_CARD_MAGICNUM), name(playerName)
{
}

manPlayer::manPlayer(Deck* deck, std::string name) :Player(deck, name)
{
}


void Player::addCard(Card card)
{
	if (card.getvalue() != -10) {
		hand.push_back(card);
		std::sort(hand.begin(), hand.end());
	}
}

void Player::drawCard(bool showAllInfo,bool hideWrongAnswer=true)
{
	std::sort(hand.begin(), hand.end());
	std::cout<<name<<"������"<<std::endl;
	//if (!showAllInfo) {
		for (int i = 0;i < hand.size();i++) {
			std::cout << i+1 << "\t";
			if (hand[i].getswiched() == true||showAllInfo) {
				std::cout <<hand[i].getnumber() << hand[i].stringColor();
			}
			else {
				std::cout << hand[i].stringColor();
				for (const auto& j : hand[i].guessList) {
					std::cout << "\tX:" << j / 2 << " ";
				}
			}
			if (hideWrongAnswer == false) {
				for (const auto& j : hand[i].guessList) {
					{
						if (j / 2 == hand[i].getnumber())continue;
					}
					std::cout << "\tX:" << j / 2 << " ";
				}
			}
			std::cout << '\n';
		}
		if (showAllInfo&&latestCard.getvalue()!= LATEST_CARD_MAGICNUM) {
			std::cout << "�ո������ģ�\t" << latestCard.getnumber() << latestCard.stringColor() << '\n';
		}
		//}
	//else {
	//	for (int i = 0;i < hand.size();i++) {
	//		std::cout <<  i << "\t"<<hand[i].getnumber() << hand[i].stringColor();
	//		std::cout << '\n';
	//	}
	//	std::cout << std::endl;
	//}
}




Card* manPlayer::choseCard()
{
	Card* ret = nullptr;
	//system("cls");
	std::cout << "���ƽ׶�\n";
	std::cout << "ͨ���������룬ѡ����ɫ��b-��ɫ��w-��ɫ,a-���\n";
	std::cout << "��ǰ�ƶ���Ŀ\n��:" << deck->cardsToDealt[BLACK].size() << " �ף�" << deck->cardsToDealt[WHITE].size() << std::endl;
	char ch;
	cardColor tmpflag = (cardColor)(!choseColorFlag);
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
				choseColorFlag = (cardColor)!choseColorFlag;
			}
			else if (ch == 'b') {
				tmpflag = BLACK;
			}
			else if (ch == 'w') {
				tmpflag = WHITE;
			}
		}
		if ((*deck).cardsToDealt[tmpflag].empty()) {
			std::cout << "�����ɫ�����Ѿ�û���ˣ�������ѡ��\n";
		}
		else {
			break;
		}
	}
	ret = (*deck).cardsToDealt[tmpflag].front();
	(*deck).cardsToDealt[tmpflag].pop();
	std::cout << "ѡ�������ǣ�" << ret->getnumber() << ret->stringColor() << std::endl;
	drawCard(true);
	return ret;
}



std::pair<int, int> manPlayer::guess(Player* target)
{
	system("cls");
	std::cout << "�²�׶�\n";
	std::cout << "��һ��" << target->name << "������ʲô��ֵ��,����Ǳ�ţ��Ҳ��Ƕ�Ӧ����Ϣ\n";
	drawCard(true,false);
	std::cout << "\n";
	target->drawCard(false);
	std::cout << "\n���ա��������-�ո�-�²����ָ�ʽ���룬�硰1 0����ʾ�²�λ��1�Ŀ�����ֵΪ0\n";
	int idx, guess;
	while (true) {
		std::cin >> idx;
		if (idx > 0 && idx <= target->hand.size()) {
			std::cin >> guess;
			break;
		}
		else {
			std::cout << "������������������\n";
		}
	}
	idx--;
	return { idx,guess };
}
void aiPlayer::generateAllGuesses(int startIdx, int endIdx, std::vector<Card>& otherHand, std::vector<SearchResult>& results)
{
	std::vector<int> currentGuess(endIdx - startIdx);
	calculateGuess(startIdx, endIdx, otherHand, results, currentGuess);
}

void aiPlayer::calculateGuess(int startIdx, int endIdx, std::vector<Card>& otherHand, std::vector<SearchResult>& results, std::vector<int>& currentGuess)
{
	if (startIdx == endIdx) {
		updateGuessCount(endIdx- currentGuess.size(), currentGuess, results);
		return;
	}
	if (otherHand[startIdx].getswiched()) {
		currentGuess[startIdx] = otherHand[startIdx].getvalue();
		calculateGuess(startIdx + 1, endIdx, otherHand, results, currentGuess);
		return;
	}
	for (int value = 0; value < MAX_CARD_NUM * 2; value++) {
		if (!isValidGuess(value, startIdx, hand, otherHand, currentGuess)) {
			continue;
		}
		currentGuess[startIdx] = value;
		calculateGuess(startIdx + 1, endIdx, otherHand, results, currentGuess);
	}
}

bool aiPlayer::isValidGuess(int value, int idx, std::vector<Card>& hand, std::vector<Card>& otherHand, std::vector<int>& currentGuess) {
	// Validate guess by considering the following conditions
	// If the value has been guessed in otherHand
	//auto res1=std::find(otherHand[idx].guessList.begin(), otherHand[idx].guessList.end(), value);
	auto res1 = otherHand[idx].guessList.find(value);
	if(res1!=otherHand[idx].guessList.end())
	{
		//std::cout << value<<" in pos"<<idx+1<<" isnot OK\n";
		return false;
	}

	// If the card with the value exists in the AI's hand
	auto res2 = std::find(hand.begin(), hand.end(), value);
	if (res2 != hand.end())
		return false;

		// If the value is greater than the previous guessed value in otherHand
	for (int i = idx;i >= 0;i--) {
		if (otherHand[i].getswiched()&& value < otherHand[i].getvalue())
			return false;
	}
	// If the value is less than the next guessed value in otherHand
	for (int i = idx+1;i < otherHand.size();i++) {
		if (otherHand[i].getswiched()&& value > otherHand[i].getvalue())
			return false;
	}

	// If the value is less than the previous guessed value in otherHand
	if(idx-1>=0&&value<= currentGuess[idx - 1])
		return false;

	//��ɫ����
	if(value % 2 != otherHand[idx].getcolor())
		return false;

	return true;
}
void aiPlayer::updateGuessCount(int d,std::vector<int>& currentGuess, std::vector<SearchResult>& results)
{
	for (int i = 0; i < currentGuess.size(); i++) {
		results[i+d].guessList[currentGuess[i]]++;
	}
	//for (auto& i : currentGuess) {
	//	std::cout << i << ' ';
	//}
	//std::cout << std::endl;
}
void aiPlayer::checkResults(std::vector<SearchResult>& results, std::vector<Card>& otherHand)
{
	for (int i = 0; i < results.size(); i++) {
		int maxidx = 0;
		int cnt = 0;
		for (int j = 0; j < results[i].guessList.size(); j++) {
			cnt+=results[i].guessList[j];
			if (results[i].guessList[j] > results[i].guessList[maxidx]) {
				maxidx = j;
			}
		}
		if (otherHand[i].getswiched()) {
			results[i].guessList[maxidx] = 0;
		}
		//auto res1 = std::find(otherHand[i].guessList.begin(), otherHand[i].guessList.end(), maxidx);
		//if (res1 != otherHand[i].guessList.end())
		//{
		//	results[i].guessList[maxidx] = 0;
		//}
		results[i].bestResult=std::make_pair(maxidx, (double)results[i].guessList[maxidx] /cnt);
	}
	std::sort(results.begin(), results.end(), [](SearchResult& a, SearchResult& b) {
		return a.bestResult.second > b.bestResult.second;
		});
}
std::pair<int, int> aiPlayer::guess(Player* target) {
	std::vector<SearchResult>results(target->hand.size());
	for (int i = 0;i < results.size();i++) {
		results[i].idx = i;
	}
		
	int lidx=0, ridx=0;
	bool flag = false;
	//for (int i = 0; i < target->hand.size(); i++) {
	//	if (target->hand[i].getswiched()) {
	//		flag = true;
	//		lidx = ridx;
	//		ridx = i;
	//		generateAllGuesses(lidx, ridx, target->hand, results);
	//	}
	//}
	if (flag == false) {
		generateAllGuesses(0, target->hand.size(), target->hand, results);
	}
	checkResults(results, target->hand);
	std::cout << "ai�²�λ��" << results[0].idx + 1 << " ׼ȷ��" << results[0].bestResult.second << std::endl;
	return std::make_pair(results[0].idx, results[0].bestResult.first / 2);
}
