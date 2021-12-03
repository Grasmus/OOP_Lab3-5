#pragma once
#include <vector>
#include "Reader.h"
class BlackList
{
	std::vector<Reader> readers;
public:
	void addToBlackList(Reader* reader);
	void eraseFromBlackList(int index);
	void showBlackList();
	bool isBlackListEmpty();
	bool isInBlackList(int index);
};

