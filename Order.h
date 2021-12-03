#pragma once
#include "Reader.h"
#include "Publisher.h"
#include <vector>

struct publishersNode
{
	Publisher publisher;
	publishersNode* next{ nullptr };
};

class Order
{
	publishersNode* pub{};
	Reader* read;
	int numOfSubs{};
public:
	Order* next{};
	Order(publishersNode* pub, Reader* read, unsigned NumOfPublishers);
	~Order();
	int getReaderIndex();
	void getReaderInfo();
	void makePurchase();
	void calcFee();
	bool checkFee();
	Reader* getReader();
	void getOrderInfo();
};

