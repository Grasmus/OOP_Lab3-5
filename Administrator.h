#pragma once
#include "Person.h"
#include <string>
#include "Order.h"
#include "BlackList.h"
#include <vector>

struct readersNode
{
	Reader reader;
	readersNode* next{nullptr};
};

class Administrator: public Person
{
	std::vector<Order> order;
	std::string Name;
	BlackList* blackListed{};
public:
	int numOfPublishers{};
	Administrator(std::string Name);
	Administrator();
	publishersNode* pub{ nullptr };
	readersNode* head{ nullptr };
	readersNode* current{ nullptr };
	void createPublishers(std::string name);
	void createPublishers(int numOfPublishers);
	void makeOrder();
	void deleteOrder(int index);
	void isBlackListEmpty();
	void getOrderInfo(int index);
	void makePurchase(int index);
	void isInBlackList(int index);
	void showBlackList();
	void savePublishers();
	void addNewReader();
	void getReaderInfo(int index);
	std::string getName();
	void addName(std::string Name);
};


