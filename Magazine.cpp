#include "Magazine.h"
#include <string>
#include <iostream>
//
//Magazine::Magazine(Publisher* publisher, int index, std::string Name)
//{
//	this->publisher = publisher;
//	this->index = index;
//	this->Name = Name;
//}

Magazine::Magazine(int index, std::string Name)
{
	this->index = index;
	this->Name = Name;
}

Magazine::Magazine(magazineData data)
{
	this->Name = data.Name;
	this->index = data.index;
}

std::string Magazine::getName()
{
	return this->Name;
}

int Magazine::getIndex()
{
	return this->index;
}