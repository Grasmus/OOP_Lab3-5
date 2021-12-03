#include "Publisher.h"
#include <iostream>
#include <fstream>

unsigned Publisher::GetIndex()
{
	return this->index;
}


std::string Publisher::GetName()
{
	return this->Name;
}
double Publisher::GetPrice() 
{
	return this->price;
}

Publisher::Publisher()
{
	std::cout << "Enter name of publisher: ";
	std::cin >> this->Name;
	std::cout << "Enter index of publisher: ";
	int k{};
	while (k <= 0)
	{
		std::cin >> k;
		if (k <= 0) std::cout << "Enter Valid index!";
	}
	this->index = k;
	std::cout << "Enter price of publisher: ";
	std::cin >> this->price;
	int numOfMagazines{}, indexOfMagazine{};
	std::string NameOfMagazine;
	std::cout << "Enter number of magazines to add: ";
	std::cin >> numOfMagazines;
	for(int i{}; i < numOfMagazines; i++)
	{
		std::cout << "Enter name of magazine: ";
		std::cin >> NameOfMagazine;
		std::cout << "Enter index of magazine: ";
		indexOfMagazine = 0;
		while (indexOfMagazine <= 0)
		{
			std::cin >> indexOfMagazine;
			if (indexOfMagazine <= 0) std::cout << "Enter Valid index!";
		}
		this->magazines.push_back(*new Magazine(/*this,*/  indexOfMagazine, NameOfMagazine));
	}
}

Publisher::~Publisher()
{
	magazines.clear();
}


Publisher::Publisher(PublisherData data, std::vector<Magazine> magazines)
{
	magazineData dataMagazine{};
	this->Name = data.Name;
	this->index = data.index;
	this->price = data.price;
	//std::cout << magazines.empty() << std::endl;
	for (unsigned i{}; i < magazines.size(); i++)
	{
		dataMagazine.Name = magazines[i].getName();
		dataMagazine.index = magazines[i].getIndex();
		this->magazines.push_back(*new Magazine(dataMagazine));
	}
}

