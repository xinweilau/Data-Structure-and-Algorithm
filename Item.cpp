/*
Team Members:
Lau Xin Wei (S10155401D)
Justin Mar Mariano Justiniano (Student_ID)

Group: ?

Highlight Feature:
-
*/

#include "stdafx.h"
#include "Item.h"
#include <iostream>
#include <string>

using namespace std;

Item::Item()
{
	Item::hitcount = 0;
}

Item::Item(string name, string description, float price, int hitcount)
{
	setName(name);
	setDescription(description);
	setPrice(price);
	Item::hitcount = hitcount;
}

Item::~Item()
{

}

string Item::getName()
{
	return Item::name;
}

void Item::setName(string name)
{
	Item::name = name;
}

string Item::getDescription()
{
	return Item::description;
}

void Item::setDescription(string description)
{
	Item::description = description;
}

float Item::getPrice()
{
	return Item::price;
}

void Item::setPrice(float price)
{
	if (price < 0.0)
	{
		Item::price = 0.0;
	}
	else 
	{ 
		Item::price = price; 
	}
}

int Item::getHitCount()
{
	return Item::hitcount;
}