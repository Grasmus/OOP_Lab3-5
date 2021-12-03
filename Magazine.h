#pragma once
#include <string>

struct magazineData {
	std::string Name;
	int index{};
};
class Magazine
{
	std::string Name;
	int index{};
	//Publisher* publisher;
public:
	//Magazine(Publisher* publisher, int index, std::string Name);
	Magazine(int index, std::string Name);
	Magazine(magazineData data);
	std::string getName();
	int getIndex();
};