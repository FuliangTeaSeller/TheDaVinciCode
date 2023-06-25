#pragma once
#include<vector>
#include"config.h"
struct SearchResult
{
	std::vector<int>guessList;//value对应的猜测次数
	int idx;//别人手牌的下标
	std::pair<int, double>bestResult;//最好的结果
	SearchResult();
	const bool operator<(const SearchResult& searchResult)const
	{
		return bestResult.second < searchResult.bestResult.second;
	}
};


