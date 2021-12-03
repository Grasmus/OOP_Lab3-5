#pragma once
#include <iostream>
#include <string>
#include "Magazine.h"
#include <vector>


struct PublisherData
{
	double price{};
	int index{};
	std::string Name;
};

class Publisher
{
	double price{};
	unsigned index{};
	std::string Name;
public:
	std::vector<Magazine> magazines;
	Publisher();
	Publisher(PublisherData data, std::vector<Magazine> magazines);
	~Publisher();
	unsigned GetIndex();
	std::string GetName();
	double GetPrice();

};

