// LauXinWei_JustinMarMarianoJustiniano.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "Item.h"
#include "AVL.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>

using namespace std;

void loadData(AVL &avlTree)
{
	cout << "Before continuing, please ensure the file name specified is with its extension (.txt) \n"
		"in the same directory as this application exe file to ensure executability (Case sentitive)\n" << endl;

	cout << "Please enter the file name: ";
	string fileName;
	cin >> fileName;

	string productName;
	string productDesc;
	float productCost;
	int hitcount;


	ifstream myfile(fileName);

	if (myfile.fail())
	{
		cout << "Failed to open " << fileName << "." << endl;
	}
	else
	{
		for (string line; getline(myfile, line);)
		{
			stringstream sstream(line);
			string item[4];

			int count = 0;
			for (string i; getline(sstream, i, ';');)
			{
				item[count] = i;
				count++;
			}

			productName = item[0];
			productDesc = item[1];
			productCost = atof(item[2].c_str());
			hitcount = atoi(item[3].c_str());

			Item prod_item(productName, productDesc, productCost, hitcount);
			avlTree.insert(prod_item);
		}
		cout << "Load Successfully." << endl;
		myfile.close();
	}
	cout << endl;
}

void saveData(AVL avlTree)
{
	if (avlTree.isEmpty())
	{
		cout << "Tree is empty." << endl;
	}
	else
	{
		cout << "Before continuing, please ensure the file name specified is with its extension (.txt) \n"
			"in the same directory as this application exe file to ensure executability (Case Sensitive)\n" << endl;
		cout << "Please enter the file name: ";

		string fileName;
		getline(cin, fileName);

		bool success = avlTree.saveData(fileName);

		if (success)
		{
			cout << "Save to file " << fileName << " successfully." << endl;
		}
		cout << endl;
	}

}

void searchItem(AVL avlTree)
{
	// Search for an Item //
	if (avlTree.isEmpty())
	{
		cout << "Tree is empty. Try adding an item or load data from a file before searching." << endl;
	}
	else
	{
		cout << "Please enter the product name to search for: ";
		string name;

		// clear the \n from previous cin //
		getline(cin, name);

		BinaryNode* item = avlTree.search(name);

		if (item != NULL)
		{
			Item prod = item->item;

			stringstream stream;
			stream << fixed << setprecision(2) << prod.getPrice();

			cout << "Product Name\tDescription\tPrice\tHit Count" << endl;
			cout << prod.getName() << "\t\t" << prod.getDescription() << setw(3) << "\t" << stream.str() << "\t" << prod.getHitCount() << endl;
		}
		else
		{
			cout << "Item not found." << endl;
		}
	}
	cout << endl;
}

void displayNumOfHits(AVL avlTree)
{
	// Search for an Item //
	if (avlTree.isEmpty())
	{
		cout << "Tree is empty. Try adding an item or load data from a file before searching." << endl;
	}
	else
	{
		cout << "Please enter the product name to search for: ";
		string name;

		// clear the \n from previous cin //
		cin.get();
		getline(cin, name);

		BinaryNode* item = avlTree.search(name);

		if (item == NULL)
		{
			cout << "There is no matching record for the item named " << name << "." << endl;
		}
		else
		{
			Item prod = item->item;
			cout << "The hit count for item: " << prod.getName() << " is " << prod.getHitCount() << "." << endl;
		}
	}
	cout << endl;
}

void displaynameAscending(AVL avlTree)
{
	if (avlTree.isEmpty())
	{
		cout << "Tree is empty. Try adding an item or load data from a file before attempting again." << endl;
	}
	else
	{
		cout << "Product Name\tDescription\tPrice\tHit Count" << endl;
		avlTree.inOrder();
	}

	cout << endl;
}

void insertItem(AVL &avlTree)
{
	string productName = "", description = "";
	float price = 0.0;
	int hitcount = 0;

	cout << "Please enter the product name: ";
	getline(cin, productName);


	cout << "Please enter product description: ";
	getline(cin, description);


	cout << "Please enter product price: ";
	cin >> price;

	cout << "Please enter hit count: ";
	cin >> hitcount;

	Item newItem(productName, description, price, hitcount);
	avlTree.insert(newItem);

	cout << endl;
	cout << "Item added!!\n" << endl;

}

void displayHitCountDescending(AVL avlTree)
{
	if (avlTree.isEmpty())
	{
		cout << "Tree is empty. Try adding an item or load data from a file before attempting again." << endl;
	}
	else
	{
		cout << "Product Name\tDescription\tPrice\tHit Count" << endl;
		avlTree.hitcountDesc();
	}
}

void displayHitCountAscending(AVL avlTree)
{
	if (avlTree.isEmpty())
	{
		cout << "Tree is empty. Try adding an item or load data from a file before attempting again." << endl;
	}
	else
	{
		cout << "Product Name\tDescription\tPrice\tHit Count" << endl;
		avlTree.hitcountAsc();
	}
}

void removeItem(AVL avlTree)
{
	if (avlTree.isEmpty())
	{
		cout << "Tree is empty. Try adding an item or load data from a file before attempting again." << endl;
	}
	else
	{
		cout << "Please enter the product name to delete: ";
		string name;

		getline(cin, name);

		BinaryNode* prod = avlTree.search(name);
		
		// if found product 
		if (prod != NULL)
		{
			Item item = prod->item;
			avlTree.remove(item);

			cout << "Delete successful!" << endl;
		}
		else
		{
			cout << "Item not found." << endl;
		}
	}
	cout << endl;
}

void displayMenu()
{
	cout << 
		"----------------------------------------------------\n"
		"      DSA Assignment by Lau Xin Wei and Justin    \n"
		"----------------------------------------------------\n"
		"                   Basic Features\n"
		"----------------------------------------------------\n"
		"1. Search for an item \n"
		"2. Display items in descending order (name) \n"
		"3. Display number of hits for for an item (name) \n"
		"4. Save Data to a File \n"
		"5. Load Data from a File \n\n"
		"----------------------------------------------------\n"
		"                   Advanced Features\n"
		"----------------------------------------------------\n"
		"6. Add a new item \n"
		"7. Remove an item \n"
		"8. Display items in descending order of hit count  \n"
		"9. Display items in ascending order of hit count \n\n"
		"----------------------------------------------------\n"
		"                       Others\n"
		"----------------------------------------------------\n"
		"0. Quit application \n\n"
		"Please select your option: ";
}

int main()
{
	AVL avlTree;
	int selection = -1;

	while (selection != 0)
	{
		displayMenu();
		char input;
		cin >> input;

		cin.get();
		if (isdigit((unsigned char) input))
		{
			selection = atoi((const char*) &input);
		}
		else
		{
			selection = -1;
		}

		// extra line for presentation purposes //
		cout << endl;

		switch (selection)
		{
		case 1:
			searchItem(avlTree);
			break;
		case 2:
			// Display items in ascending order (name) //
			displaynameAscending(avlTree);
			break;
		case 3:
			// Display number of hits for an item (name) //
			displayNumOfHits(avlTree);
			break;
		case 4:
			// Save Data to a File //
			saveData(avlTree);
			break;
		case 5:
			 // Load Data from a File //
			loadData(avlTree);
			break;
		case 6:
			// Add a new Item //
			insertItem(avlTree);
			break;
		case 7:
			// Remove an Item //
			removeItem(avlTree);
			break;
		case 8:
			// Display item in descending order of hit count //
			displayHitCountDescending(avlTree);
			break;
		case 9:
			// Display item in descending order of hit count //
			displayHitCountAscending(avlTree);
			break;
		case 0:
			cout << "Thank you for using this system. Good Bye!" << endl;
			break;
		default:
			cin.get();
			cout << "Invalid input given. Please enter a valid option. \n" << endl;
			break;
		}
	}


	system("PAUSE");
    return 0;
}

