#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include "Administrator.h"
#include "Person.h"
#include "Publisher.h"

using std::cout;
using std::cin;

int main()
{
	std::string nameOfAdmin;
	cout << "Enter the name of admin: ";
	cin >> nameOfAdmin;

	std::string nameOfReader;
	cout << "Enter the name of reader: ";
	cin >> nameOfReader;

	Administrator admin(nameOfAdmin);

	Person* adminP;
	adminP = new Administrator(nameOfAdmin);
	cout << "Admin name (first method): " << adminP->getName() << std::endl;
	delete(adminP);
	adminP = new Reader();
	adminP->addName(nameOfReader);
	cout << "Readr name (first method): " << adminP->getName() << std::endl;
	delete(adminP);

	Administrator adminitrator;
	Reader reader;
	adminP = &adminitrator;
	adminP->addName(nameOfAdmin);
	cout << "Admin name (second method): " << adminP->getName() << std::endl;

	adminP = &reader;
	adminP->addName(nameOfReader);
	cout << "Readr name (second method): " << adminP->getName() << std::endl;

	Administrator adminitrator2(nameOfAdmin);
	Reader reader2;
	reader2.addName(nameOfReader);
	adminP = (Person*)&adminitrator2;
	cout << "Admin name (third method): " << adminP->getName() << std::endl;
	adminP = (Person*)&reader2;
	cout << "Readr name (third method): " << adminP->getName() << std::endl;

	cout << "Create publishers (1) or load existing from file (2): ";
	int choice{};
	std::string nameOfFile{};
	int numberOfPublishers{}, indexOfReader{};
	std::ifstream inf{};
	do
	{
		std::cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "Enter number of Publisher to create: ";
			cin >> numberOfPublishers;
			try
			{
				admin.createPublishers(numberOfPublishers);
			}
			catch (std::string error)
			{
				std::cerr << error << std::endl;
				exit(1);
			}
			try
			{
				admin.savePublishers();
			}
			catch (std::string error)
			{
				std::cerr << error << std::endl;
				exit(1);
			}
			break;
		case 2:
			std::cout << "Enter name of file: ";
			std::cin >> nameOfFile;
			try
			{
				admin.createPublishers(nameOfFile);
			}
			catch (std::string error)
			{
				std::cerr << error << std::endl;
				exit(1);
			}
			break;
		default:
			std::cout << "Enter 1 for first choice or 2 for second.";
			break;
		}
	} while (choice != 1 && choice != 2);
	system("cls");
	std::cout << "Recreate publishers (1)\nMake order(2)\n";
	do
	{
		std::cin >> choice;
		switch (choice)
		{
		case 1:
			std::cout << "Enter number of Publisher to create: ";
			cin >> numberOfPublishers;
			admin.createPublishers(numberOfPublishers);
			break;
		case 2:
			try
			{
				admin.makeOrder();
			}
			catch (std::string error)
			{
				std::cerr << error << std::endl;
				exit(1);
			}
			break;
		default:
			std::cout << "Enter 1 for first choice or 2 for second.";
			break;
		}
	} while (choice != 1 && choice != 2 && choice != 3);
	system("cls");
	do
	{
		std::cout << "Make new order (1)\nMake a purchase (2)\nGet order info (3)\nGet reader info (4)\nShow blacklist (5)\nRemove order (6)\nExit (7)\n";
		std::cin >> choice;
		switch (choice)
		{
		case 1:
			try
			{
				admin.makeOrder();
			}
			catch (std::string error)
			{
				std::cerr << error << std::endl;
				exit(1);
			}
			break;
		case 2:
			std::cout << "Enter index of reader: ";
			std::cin >> indexOfReader;
			admin.makePurchase(indexOfReader);
			break;
		case 3:
			std::cout << "Enter index of reader: ";
			std::cin >> indexOfReader;
			admin.getOrderInfo(indexOfReader);
			break;
		case 4:
			std::cout << "Enter index of reader: ";
			std::cin >> indexOfReader;
			admin.getReaderInfo(indexOfReader);
			break;
		case 5:
			admin.showBlackList();
			break;
		case 6:
			std::cout << "Enter index of reader: ";
			std::cin >> indexOfReader;
			admin.deleteOrder(indexOfReader);
			break;
		case 7:
			return 0;
		default:
			std::cout << "Enter valid choice.";
			break;
		}
		system("cls");
	} while (1);
	return 0;
}