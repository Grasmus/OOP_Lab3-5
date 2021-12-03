#include "BlackList.h"
#include <iostream>
#include <vector>

void BlackList::addToBlackList(Reader* reader)
{
	this->readers.push_back(*reader);
}

void BlackList::eraseFromBlackList(int index)
{
	int j{};
	for (auto i{ readers.begin() }; i != readers.end(); i++, j++)
	{
		if (readers[j].getIndex() == index)
		{
			readers.erase(i);
			return;
		}
	}
	std::cout << "There is no such reader with index " << index << " in Blacklist";
}

void BlackList::showBlackList()
{
	std::cout << "Readers on blacklist: " << std::endl;
	if(readers.size())
	{
		for (int i{}; i < readers.size(); i++)
		{
			std::cout << "Reader name: " << readers[i].getName() << std::endl;
			std::cout << "Reader surname: " << readers[i].printSurname() << std::endl;
			std::cout << std::endl;
		}
		
	}
	else
	{
		std::cout << "Blacklist is empty!" << std::endl;
	}

		std::cin.get();
	std::cin.get();
}

bool BlackList::isInBlackList(int index)
{
	for (int i{}; i < readers.size(); i++)
	{
		if (readers[i].getIndex() == index) return true;
	}
	return false;
}

bool BlackList::isBlackListEmpty()
{
	if (this->readers.size() == 0)
	{
		return true;
	}
	else return false;
}