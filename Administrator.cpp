#include "Administrator.h"
#include "Publisher.h"
#include <iostream>
#include <fstream>
#include <vector>

std::string Administrator::getName()
{
	return this->Name;
}

void Administrator::makeOrder()
{
	std::string memory_alloc_error{ "Error while allocating memory." };
	int answer{}, index{};
		std::cout << "Create new reader (1) or order existing one (2)?";
		std::cin >> answer;
		if (answer == 1)
		{
			try
			{
				addNewReader();
			}
			catch (std::exception memory_alloc_error)
			{
				std::cerr << "Error while allocating memory.";
				exit(1);
			}
			this->order.push_back(*(new Order(this->pub, &this->head->reader, this->numOfPublishers)));
			if (!&this->order.back())
			{
				throw(memory_alloc_error);
			}
		}
		else if (answer == 2)
		{
			if (head)
			{
				std::cout << "Enter index of reader: ";
				std::cin >> index;
				current = head;
				while (current)
				{
					if (index == this->current->reader.getIndex())
					{
						this->order.push_back(*(new Order(this->pub, &this->current->reader, this->numOfPublishers)));
						if (!&this->order.back())
						{
							throw(memory_alloc_error);
						}
						return;
					}
					current = current->next;
				}
				std::cout << "There is no creadted readers with index " << index << std::endl;
			}
			else
			{
				std::cout << "There is no created readers." << std::endl;
				std::cin.get();
				std::cin.get();
			}
				
		}
}

Administrator::Administrator(std::string Name)
{
	this->Name = Name;
}

Administrator::Administrator()
{
}

void Administrator::addName(std::string Name)
{
	this->Name = Name;
}

//void Administrator::createReaders(std::string name)
//{
//	ReaderData ReaderData{};
//	std::ifstream inf{};
//	inf.open(name);
//	if (inf.is_open())
//	{
//		while (inf >> ReaderData.Name)
//		{
//			//inf.read((char*)&r, sizeof(Data));
//			inf >> ReaderData.Surname;
//			inf >> ReaderData.fee;
//			inf >> ReaderData.index;
//			inf >> ReaderData.isInBlackList;
//			inf >> ReaderData.lastPurchase.day;
//			inf >> ReaderData.lastPurchase.month;
//			inf >> ReaderData.lastPurchase.year;
//			inf >> ReaderData.numOfSubs;
//			inf >> ReaderData.paidFor.day;
//			inf >> ReaderData.paidFor.month;
//			inf >> ReaderData.paidFor.year;
//			inf >> ReaderData.regDate.day;
//			inf >> ReaderData.regDate.month;
//			inf >> ReaderData.regDate.year;
//
//			if (this->head)
//			{
//				this->current = new Reader(ReaderData, this->pub);
//				this->current->subsPubs = new int[ReaderData.numOfSubs];
//				for (int i{}; i < ReaderData.numOfSubs; i++)
//				{
//					inf >> this->current->subsPubs[i];
//				}
//				this->current->setNode(this->head);
//				this->head = this->current;
//			}
//			else
//			{
//				this->head = new Reader(ReaderData, this->pub);
//				this->head->subsPubs = new int[ReaderData.numOfSubs];
//				for (int i{}; i < ReaderData.numOfSubs; i++)
//				{
//					inf >> this->head->subsPubs[i];
//				}
//			}
//		}
//		inf.close();
//		//std::cout << "Closed" << std::endl;
//		//std::cin.get();
//	}
//	else std::cout << "Error reading file!";
//	//std::cout << "Ended" << std::endl;
//}

void Administrator::addNewReader()
{
	std::string memory_alloc_error{ "Error while allocating memory." };
	if (head)
	{
		current = new readersNode();
		if (current)
		{
			current->next = head;
			head = current;
		}
		else
		{
			throw(memory_alloc_error);
		}
	}
	else
	{
		head = new readersNode();
		if (head)
		{
			current = head;
		}
		else throw(memory_alloc_error);
	}
}




void Administrator::deleteOrder(int index)
{
	int j{};
	for (auto i{ this->order.begin()}; i != this->order.end(); i++, j++)
	{
		if (index == this->order[j].getReaderIndex())
		{
			this->order.erase(i);
			return;
		}
	}
	std::cout << "There is no such order with index " << index << std::endl;
}

void Administrator::getOrderInfo(int index)
{

	for (unsigned i{}; i < this->order.size(); i++)
	{
		if (index == this->order[i].getReaderIndex())
		{
			this->order[i].getOrderInfo();
			return;
		}
	}
	std::cout << "Reader with index " << index << " does not have orders." << std::endl;
	
}

void Administrator::getReaderInfo(int index)
{
	this->current = this->head;
	while (current)
	{
		if (current->reader.getIndex() == index)
		{
			std::cout << "Reader name: " << current->reader.getName();
			std::cout << std::endl;
			std::cout << "Reader surname: " << current->reader.printSurname();
			std::cout << std::endl;
			Date d{ current->reader.getRegDate() };
			std::cout << "Registration date: " << d.day << "." << d.month << "."
				<< d.year << std::endl;
			std::cin.get();
			std::cin.get();
			return;
		}
		current = current->next;
		
	}
	std::cout << "There is no reader with index " << index << std::endl;
}
void Administrator::makePurchase(int index)
{
	for(unsigned i{}; i < order.size(); i++)
	{
		if (index == this->order[i].getReaderIndex())
		{
			this->order[i].makePurchase();
			try
			{
				isInBlackList(index);
			}
			catch (std::exception memory_alloc_error)
			{
				std::cerr << "Error while allocating memory.";
				exit(1);
			}
			return;
		}
	}
	std::cout << "There is no such user with index " << index << std::endl;
}

void Administrator::isInBlackList(int index)
{
	std::string memory_alloc_error{ "Error while allocating memory." };
	for (unsigned i{}; i < order.size(); i++)
	{
		if (index == this->order[i].getReaderIndex())
		{
			if (this->order[i].checkFee())
			{
				//std::cout << this->order[i].getReader()->printName() << ' ' << this->order[i].getReader()->printSurname() << " is NOT in blacklist." << std::endl;
				if (blackListed)
				{
					if (blackListed->isInBlackList(index))
					{
						blackListed->eraseFromBlackList(index);
					}
				}
			}
			else
			{
				if (blackListed)
				{
					blackListed->addToBlackList(order[i].getReader());
				}
				else
				{
					blackListed = new BlackList;
					if (blackListed) blackListed->addToBlackList(order[i].getReader());
					else throw(memory_alloc_error);
				}
			}
			
		}
	}
}

void Administrator::showBlackList()
{
	if (blackListed)
	{
		blackListed->showBlackList();
		isBlackListEmpty();
	}
	else
	{
		std::cout << "Blacklist is empty!" << std::endl;
	}
	std::cin.get();
	std::cin.get();
}

void Administrator::isBlackListEmpty()
{
	if (this->blackListed->isBlackListEmpty())
	{
		delete this->blackListed;
		this->blackListed = nullptr;
	} 
}

void Administrator::createPublishers(std::string name)
{
	std::string file_read_error{ "Reading error." };
	std::string file_open_error{ "Error while opening file." };
	std::string memory_alloc_error{ "Error while allocating memory." };
	PublisherData data;
	publishersNode* current{};
	Publisher* temp{};
	std::vector<Magazine> magazines;
	std::string NameOfMagazine;
	int indexOfMagazine{};
	int numOfMagazines{};
	std::ifstream inf{};
		inf.open(name);
		if (inf.fail())
		{
			throw(file_open_error);
		}
		else
		{
			inf >> this->numOfPublishers;
			if (inf.fail()) throw(file_read_error);
			else
			{
				while (inf >> data.Name)
				{
					if (inf.fail()) throw(file_read_error);
					else
					{
						inf >> data.index;
						inf >> data.price;
						inf >> numOfMagazines;
						if (inf.fail()) throw(file_read_error);
						else
						{
							for (int i{}; i < numOfMagazines; i++)
							{
								inf >> NameOfMagazine;
								inf >> indexOfMagazine;
								if(inf.fail()) throw(file_read_error);
								else
								{
									magazines.push_back(*new Magazine(indexOfMagazine, NameOfMagazine));
								}
							}
							if (this->pub)
							{
								current->next = new publishersNode{ *new Publisher(data, magazines) , nullptr };
								if (current->next)
								{
									current = current->next;
								}
								else
								{
									throw(memory_alloc_error);
								}
							}
							else
							{
								this->pub = new publishersNode{ *new Publisher(data, magazines) , nullptr };
								if (this->pub)
								{
									current = pub;
								}
								else
								{
									throw(memory_alloc_error);
								}
							}
							magazines.clear();
						}
						current = pub;
						for (int i{}; i < numOfPublishers; i++)
						{
							std::cout << current->publisher.GetName() << '\t';
							for (unsigned j{}; j < current->publisher.magazines.size(); j++)
							{
								std::cout << current->publisher.magazines[j].getName() << '\t';
							}
							std::cout << std::endl;
							current = current->next;
						}
						}
					}
				inf.close();
			}
		}
}

void Administrator::createPublishers(int numOfPublishers)
{	
	std::string memory_alloc_error{ "Error while allocating memory." };
	publishersNode* temp{pub};
	if (pub)
	{
		for (int i{}; i < numOfPublishers; i++)
		{
			pub = pub->next;
			delete temp;
			temp = pub;
		}
	}
	this->numOfPublishers = numOfPublishers;
	publishersNode * current{};
	pub = new publishersNode;
	if (pub)
	{
		current = pub;
		for (int i{}; i < this->numOfPublishers - 1; i++)
		{
			temp = new publishersNode;
			if (temp)
			{
				current->next = temp;
				current = current->next;
			}
			else
			{
				throw(memory_alloc_error);
			}
			
		}
	}
	else
	{
		throw(memory_alloc_error);
	}
}

void Administrator::savePublishers()
{
	std::string file_open_error{"Error while opening file."};
	std::string file_writing_error{"Writing error."};
	std::ofstream outf{};
	outf.open("Publishers.dat");
	publishersNode * current{pub};
	if (outf.fail())
	{
		throw file_open_error;
	}
	else
	{
		outf << this->numOfPublishers << std::endl;
		if (outf.fail()) throw(file_writing_error);
		else
		{
			for (int i{}; i < this->numOfPublishers; i++)
			{
				outf << current->publisher.GetName() << '\t' << current->publisher.GetIndex() << '\t' << current->publisher.GetPrice() << '\t' << current->publisher.magazines.size() << '\t';
				if (outf.fail()) throw(file_writing_error);
				else
				{
					for (unsigned j{}; j < current->publisher.magazines.size(); j++)
					{
						outf << current->publisher.magazines[j].getName() << '\t' << current->publisher.magazines[j].getIndex() << '\t';
						if (outf.fail())
						{
							throw(file_writing_error);
						}
					}
					outf << std::endl;
					current = current->next;
				}
			}
			outf.close();
		}
	}
}