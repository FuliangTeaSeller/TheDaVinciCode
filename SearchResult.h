#pragma once
#include<vector>
#include"config.h"
struct SearchResult
{
	std::vector<int>guessList;//value��Ӧ�Ĳ²����
	int idx;//�������Ƶ��±�
	std::pair<int, double>bestResult;//��õĽ��
	SearchResult();
	const bool operator<(const SearchResult& searchResult)const
	{
		return bestResult.second < searchResult.bestResult.second;
	}
};


