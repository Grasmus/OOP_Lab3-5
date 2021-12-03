#pragma once
#include "Person.h"
#include <string>


struct Date {
	int day{};
	int month{};
	int year{};
};

struct ReaderData {
	std::string Name;
	std::string Surname;
	bool isInBlackList = false;
	Date regDate;
	Date lastPurchase{};
	Date paidFor{};
	int numOfSubs;
	double fee;
	short index;
};

class Reader: public Person
{
	std::string Name;
	std::string Surname;
	Date regDate;
	Date lastPurchase{};
	Date paidFor{};
	short index;
public:
	Reader();
	void addName(std::string Name);
	double fee{};
	void setLastPurchase(Date d);
	void setPaidFor(Date d);
	std::string printSurname();
	Date getLastPurchase();
	Date getRegDate();
	double getFee();
	short getIndex();
	Date getPaidFor();
	std::string getName();
};

