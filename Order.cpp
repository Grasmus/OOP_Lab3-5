#define _CRT_SECURE_NO_WARNINGS
#include "Order.h"
//#include "Administrator.h"

#include <iostream>
#include <vector>

Order::Order(publishersNode* pub, Reader* read, unsigned NumOfPublishers)
{
	this->read = read;
	unsigned numOfPublishers{ NumOfPublishers };
	publishersNode* current{ pub };
	unsigned n{};
	while (n <= 0 || n > numOfPublishers)
	{
		std::cout << "Enter number of subscriptions: ";
		std::cin >> n;
		if (n <= 0 || n > numOfPublishers) std::cout << "Enter valid number!" << std::endl;
	}
	this->numOfSubs = n;
	int* tempPublisherIndex = new int[numOfPublishers];
	for (unsigned i{}; i < numOfPublishers; i++) {
		tempPublisherIndex[i] = current->publisher.GetIndex();
		current = current->next;
	}
	int p{};
	bool isValid{ false };
	for (unsigned i{}; i < n; i++)
	{
		unsigned k{};
		isValid = false;
		std::cout << "Available publishers: \n";
		current = pub;
		for (unsigned i{}; i < numOfPublishers; i++)
		{
			std::cout << current->publisher.GetName() << " = " << current->publisher.GetIndex() << '\t' << "price: " << current->publisher.GetPrice() << std::endl;
			current = current->next;
		}

		while (1)
		{
			std::cout << "Enter the index of publisher: ";
			std::cin >> p;
			for (k = 0; k < numOfPublishers; k++)
			{
				if (p == -1) { std::cout << "Enter valid number!" << std::endl; break; }
				else if (tempPublisherIndex[k] == p) {
					tempPublisherIndex[k] = -1;  isValid = true; break;
				}
			}
			if (isValid) break;
			else
				std::cout << "Enter valid number!" << std::endl;
		}
		/*this->pub.push_back(pub[k]);
		for (int i{}; i < this->pub.back().magazines.size(); i++)
		{
			std::cout << this->pub.back().magazines[i].getName() << '\t' << std::endl;
		}
		this->pub.back().magazines.clear();
		for (int i{}; i < pub[k].magazines.size(); i++)
		{
			std::cout << pub[k].magazines[i].getName() << '\t';
		}
		std::cin.get();
		std::cin.get();*/

		current = pub;
		publishersNode* currentSub{};
	
		for (unsigned i{}; i < numOfPublishers; i++)
		{
			if (current->publisher.GetIndex() == p)
			{
				if (this->pub)
				{
					currentSub = new publishersNode{ *new Publisher(current->publisher), nullptr };
					currentSub->next = this->pub;
					this->pub = currentSub;
				}
				else
				{
					this->pub = new publishersNode{ *new Publisher(current->publisher), nullptr };
					currentSub = this->pub;
				}
				break;
			}
			else current = current->next;
		}
		
		
		unsigned numOfMagazines{};
		unsigned indexOfMagazine{};
		while (1)
		{
			std::cout << "Enter number of magazines to add: ";
			std::cin >> numOfMagazines;
			if (numOfMagazines > 0 && numOfMagazines <= current->publisher.magazines.size()) break;
		}
		if (this->pub)
		{
			this->pub->publisher.magazines.clear();
		}

		unsigned* tempMagazineIndex = new unsigned[current->publisher.magazines.size()];
		if (tempMagazineIndex)
		{
			for (unsigned j{}; j < current->publisher.magazines.size(); j++)
			{
				tempMagazineIndex[j] = current->publisher.magazines[j].getIndex();
			}
			for (unsigned i{}; i < numOfMagazines; i++)
			{
				std::cout << "Available magazines: " << std::endl;
				for (unsigned j{}; j < current->publisher.magazines.size(); j++)
				{
					std::cout << current->publisher.magazines[j].getName() << " = " << current->publisher.magazines[j].getIndex() << std::endl;
				}

				isValid = false;
				while (1)
				{
					std::cout << "Enter the index of magazine: ";
					std::cin >> indexOfMagazine;
					for (k = 0; k < current->publisher.magazines.size(); k++)
					{
						if (indexOfMagazine == 0) { std::cout << "Enter valid number!" << std::endl; break; }
						else if (tempMagazineIndex[k] == indexOfMagazine) {
							tempMagazineIndex[k] = 0;  isValid = true; break;
						}
					}
					if (isValid) break;
					else
						std::cout << "Enter valid number!" << std::endl;
				}
				magazineData temp{};
				for (unsigned j{}; j < current->publisher.magazines.size(); j++)
				{
					if (current->publisher.magazines[j].getIndex() == indexOfMagazine)
					{
						temp.Name = current->publisher.magazines[j].getName();
						temp.index = current->publisher.magazines[j].getIndex();
						this->pub->publisher.magazines.push_back(*new Magazine(temp));
					}
				}

			}
		}
		
	}
	calcFee();
}

int Order::getReaderIndex()
{
	return read->getIndex();
}

Order::~Order()
{
	publishersNode* temp{ pub };
	for (int i{}; i < this->numOfSubs; i++)
	{
		pub = pub->next;
		delete temp;
		temp = pub;
	}
}
void Order::getReaderInfo()
{
	std::cout << "Reader name: " << read->getName();
	std::cout << std::endl;
	std::cout << "Reader surname: " << read->printSurname();
	std::cout << std::endl;
	Date d{ read->getRegDate() };
	std::cout << "Registration date: " << d.day << "." << d.month << "."
		<< d.year << std::endl;
	std::cin.get();
	std::cin.get();
	return;
}

void Order::makePurchase()
{
	int month{};
	std::cout << "Enter num of paid months: ";
	std::cin >> month;
	std::time_t t = std::time(0);
	std::tm* now = std::localtime(&t);
	int day = now->tm_mday;
	Date today{ day, now->tm_mon + 1, now->tm_year + 1900 };
	if (!read->getLastPurchase().year)
	{
		read->setLastPurchase(today);
	}
	Date d = read->getPaidFor();
	for (int i{}; i < month; i++)
	{
		if (d.month < 12)
		{
			d.month++;
		}
		else
		{
			d.year++;
			d.month = 0;
		}
	}
	d.month++;
	read->setPaidFor(d);
}

void Order::calcFee()
{
	publishersNode* current{ pub };
	this->read->fee = 0.0;
	for (int i{}; i < this->numOfSubs; i++)
	{
		this->read->fee += current->publisher.GetPrice();
		current = current->next;
	}
}

bool Order::checkFee()
{
	std::time_t t = std::time(0);
		std::tm* now = std::localtime(&t);
		int day = now->tm_mday;
		Date today{ day, now->tm_mon + 1, now->tm_year + 1900 };
		Date nextPurchase = this->read->getPaidFor();
		Date overdue{};
		if (nextPurchase.year > today.year || nextPurchase.month > today.month)
		{
			overdue = { 0, 0, 0 };
			//this->isInBlackList = false;
			//std::cout << this->Name << " " << this->Surname << " doesn`t have overdue" << std::endl;
			return true;
		}
		else if (nextPurchase.year < today.year) {
			overdue.year = today.year - nextPurchase.year;
			overdue.month = static_cast<int>(fabs(today.month - nextPurchase.month));
			if (today.day < nextPurchase.day)
			{
				overdue.day = nextPurchase.day - today.day;
			}
			else
			{
				overdue.day = today.day - nextPurchase.day;
			}
			return false;
			/*std::cout << this->Name << " " << this->Surname
				<< " has an ovedue for: " << overdue.day << " days " << overdue.month
				<< " month " << overdue.year << " years " << std::endl;*/
		}
		else if (nextPurchase.year == today.year)
		{
			overdue.year = 0;
			if (today.month > nextPurchase.month)
			{
				overdue.month = today.month - nextPurchase.month;
			}
			if (today.day < nextPurchase.day)
			{
				overdue.day = nextPurchase.day - today.day;
			}
			else
			{
				overdue.day = today.day - nextPurchase.day;
			}
			return false;
			/*std::cout << this->Name << " " << this->Surname
				<< " has an ovedue for: " << overdue.day << " days " << overdue.month
				<< " month " << overdue.year << " years " << std::endl;*/
		}
}

Reader* Order::getReader()
{
	return read;
}

void Order::getOrderInfo()
{
	publishersNode* current{ pub };
	std::cout << "Reader name: " << read->getName();
	std::cout << std::endl;
	std::cout << "Reader surname: " << read->printSurname();
	std::cout << std::endl;
	Date d{};
	if (read->getLastPurchase().year != 0)
	{
		d = read->getLastPurchase();
		std::cout << "Last purchase date: " << d.day << "." << d.month << "."
			<< d.year << std::endl;
		d = read->getPaidFor();
		std::cout << "Paid for: " << d.day << "." << d.month << "."
			<< d.year << std::endl;
		std::cout << "Fee: " << read->getFee() << std::endl;
	}
	std::cout << "Number of subscriptions: " << this->numOfSubs << std::endl;
	for (int i{}; i < this->numOfSubs; i++)
	{
		std::cout << "Publisher name: " << current->publisher.GetName() << std::endl;
		std::cout << "Publisher price: " << current->publisher.GetPrice() << std::endl;
		std::cout << "Subscripted magazines: ";
		for (unsigned j{}; j < current->publisher.magazines.size(); j++)
		{
			std::cout << current->publisher.magazines[j].getName() << '\t';
		}
		current = current->next;
	}
	std::cin.get();
	std::cin.get();
}