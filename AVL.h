#pragma once
#include "BinaryNode.h"
#include "Item.h"
#include <fstream>
typedef Item ItemType;

class AVL
{
private:
	BinaryNode* root; // Root Node of the Tree
	BinaryNode* firstHitCountNode; // Represents the product with smallest hit count of the tree

public:
	AVL(); // Constructor 
	~AVL(); // Deconstructor

	void inOrder(); // traverse the tree In-Order
	void inOrder(BinaryNode* node); // traverse the tree In-Order
	void postOrder(); // traverse the tree in Post-Order
	void postOrder(BinaryNode* node); // traverse the tree in Post-Order
	void preOrder(); // traverse the tree in Pre-Order 
	void preOrder(BinaryNode* node); // traverse the tree in Pre-Order
	void hitcountAsc(); // traverse the hitcounts list in ascending order
	void hitcountDesc(); // traverse the hitcounts list in descending order
	void insertHitCount(BinaryNode* &countNode, BinaryNode* item); // add a new hitcount
	void removeHitCount(BinaryNode* &countNode, ItemType item); // deassociate item's hitcount from the list
	void insert(ItemType item); // insert an item into the tree
	BinaryNode* insert(BinaryNode* rootNode, BinaryNode* item); // insert an item into the tree
	void remove(ItemType item); // remove an item from the tree
	BinaryNode* remove(BinaryNode* rootNode, ItemType item); // remove an item from the tree
	bool isEmpty(); // check if the tree is empty
	int numOfNodes(BinaryNode* rootNode); // count the number of nodes in a tree
	BinaryNode* getMinValueItem(BinaryNode* node); // Given a non-empty tree, return the item with the smallest value (name) in that tree
	BinaryNode* search(string name); // Search for an item given the product name 
	BinaryNode* search(BinaryNode* rootNode, string name);
	BinaryNode* rightRotate(BinaryNode* node); // perform right rotation on the child node (item) of sub-tree
	BinaryNode* leftRotate(BinaryNode* node); // perform left rotation on the child node (item) of sub-tree
	int max(int val1, int val2); // utility function to get the maximum of 2 integers
	int getHeight(BinaryNode* item); // retrieve the height of the tree
	int getBalance(BinaryNode* node); // get balance factor of BinaryNode
	bool saveData(string fileName); // save tree's data into a file 
	void inOrderSave(BinaryNode* node, ofstream &stream); // save tree's data into a file
};