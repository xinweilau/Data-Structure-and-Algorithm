#pragma once
#include "Item.h"

struct BinaryNode {

	Item item; // pointer to item object
	
	// BST Nodes
	BinaryNode* left; // pointer to left leaf 
	BinaryNode* right; // pointer to right leaf

	// Double-ended Hit Count //
	BinaryNode* prevHitCount; // pointer to a smaller hitcount
	BinaryNode* nextHitCount; // pointer to a higher hitcount

	unsigned char height; // height of the tree

};