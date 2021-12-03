#pragma once
#include <string>

class Person
{

public:
	virtual std::string getName() = 0;
	virtual void addName(std::string Name) = 0;
};

