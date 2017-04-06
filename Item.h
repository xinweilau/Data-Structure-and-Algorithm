#pragma once
#include <string>
using namespace std;

class Item
{
	private:
		string name;
		string description;
		float price;
		int hitcount;

	public:
		Item();
		Item(string name,  string description, float price, int hitcount);
		~Item();

		string getName();
		void setName(string name);
		string getDescription();
		void setDescription(string description);
		
		float getPrice();
		void setPrice(float name);

		int getHitCount();
};