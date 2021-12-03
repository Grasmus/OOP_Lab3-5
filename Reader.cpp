#define _CRT_SECURE_NO_WARNINGS
#include "Reader.h"
#include <iostream>
#include <string.h>
#include <fstream>
#include <ctime>
#include <math.h>


std::string Reader::getName()
{
	return this->Name;
}

Reader::Reader()
{
	std::cout << "Enter name of reader: ";
	std::cin >> this->Name;
	std::cout << "Enter surnamename of reader: ";
	std::cin >> this->Surname;
	std::cout << "Enter index of reader: ";
	std::cin >> this->index;
	std::time_t t = std::time(0);
	std::tm* now = localtime(&t);
	int day = now->tm_mday;
	Date today{ day, now->tm_mon + 1, now->tm_year + 1900 };
	this->regDate = today;
	this->paidFor = today;
	//calcFee();
}


void Reader::addName(std::string Name)
{
	this->Name = Name;
}



std::string Reader::printSurname()
{
	return this->Surname;
}

Date Reader::getRegDate()
{
	return this->regDate;
}



double Reader::getFee()
{
	return this->fee;
}

short Reader::getIndex()
{
	return this->index;
}

void Reader::setLastPurchase(Date d)
{
	this->lastPurchase = d;
}

Date Reader::getLastPurchase()
{
	return this->lastPurchase;
}

Date Reader::getPaidFor()
{
	return this->paidFor;
}

void Reader::setPaidFor(Date d)
{
	this->paidFor = d;
}

