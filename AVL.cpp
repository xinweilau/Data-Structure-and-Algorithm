/*
Team Members: 
Lau Xin Wei (S10155401D)
Justin Mar Mariano Justiniano (Student_ID)

Group: ?

Highlight Feature:
-
*/

#include "stdafx.h"
#include "AVL.h"
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

AVL::AVL()
{
	root = NULL;
	firstHitCountNode = NULL;
}

AVL::~AVL()
{

}

void AVL::insert(ItemType item)
{
	BinaryNode* newNode = new BinaryNode();
	newNode->item = item;

	newNode->left = NULL;
	newNode->right = NULL;

	newNode->prevHitCount = NULL;
	newNode->nextHitCount = NULL;

	newNode->height = 1;

	root = insert(root, newNode);
	insertHitCount(firstHitCountNode, newNode);
}

BinaryNode* AVL::insert(BinaryNode* rootNode, BinaryNode* item)
{
	/* Insert new BinaryNode into the tree */
	if (rootNode == NULL)
	{
		return item;
	}

	if (item->item.getName() <= rootNode->item.getName())
	{
		rootNode->left = insert(rootNode->left, item);
	}
	else if (item->item.getName() > rootNode->item.getName())
	{
		rootNode->right = insert(rootNode->right, item);
	}

	/* 2. Update Height of Parent Node */
	rootNode->height = 1 + max(getHeight(rootNode->left), getHeight(rootNode->right));

	/* 
	3. Check the balance factor of the Parent Node 
	   and if depending on the balance factor and
	   conditions, it will rotate the nodes accordingly 
		  
	   The balance factor will determine if the tree/sub-tree is balanced
	*/
	int balance = getBalance(rootNode);


	// Left Left Case - Perform a Right Rotation */
	if (balance > 1 && item->item.getName() < rootNode->left->item.getName())
	{
		return rightRotate(rootNode);
	}

	// Right Right Case - Perform a Left Rotation */
	if (balance < -1 && item->item.getName() > rootNode->right->item.getName())
	{
		return leftRotate(rootNode);
	}

	// Left Right Case - Perform a Left-Right Rotation */
	if (balance > 1 && item->item.getName() > rootNode->left->item.getName())
	{
		rootNode->left = leftRotate(rootNode->left);
		return rightRotate(rootNode);
	}

	/* Right Left Case - Peform a Right-Left Rotation */
	if (balance < -1 && item->item.getName() < rootNode->right->item.getName())
	{
		rootNode->right = rightRotate(rootNode->right);
		return leftRotate(rootNode);
	}

	/* return the (unchanged) node pointer */
	return rootNode;
}

void AVL::insertHitCount(BinaryNode* &countNode, BinaryNode* item)
{
	 // if there is nothing in the tree yet //
	if (countNode == NULL)
	{
		countNode = item;
		
		/*
		Description: Set the countNode's prevHitCount and nextHitCount to itself
		Type of Data Structure: circular linked list

		Time Complexity:
		Insertion of Highest and Lowest Hit Count - O(1)
		Average - O(n)
		
		*/
		countNode->prevHitCount = item;
		countNode->nextHitCount = item;
	}
	else
	{
		// determine if the new item is equal to or higher in comparison to the last item in the circular linked list //
		bool highestHitCount = (item->item.getHitCount() >= firstHitCountNode->prevHitCount->item.getHitCount());

		// determine if the new item is lowest in comparison to first item in the circular linked list //
		bool lowestHitCount = (item->item.getHitCount() < firstHitCountNode->item.getHitCount());

		// determine if the new item's hit count is smaller than the next item in the list's hit count //
		bool lowerHitCount = (item->item.getHitCount() <= countNode->item.getHitCount());

		if (highestHitCount)
		{
			// Get the current item in the list with the highest hit count // 
			BinaryNode* currentHighest = countNode->prevHitCount;

			// set the new item's next pointer to the first item in the list //
			item->nextHitCount = countNode;

			// set the new item's previous pointer to the current last item //
			item->prevHitCount = currentHighest;

			// set the first item in the list's previous pointer to the new item //
			countNode->prevHitCount = item;

			// set the current item in the list with the highest hit count's pointer to
			currentHighest->nextHitCount = item;
		}
		else if (lowestHitCount)
		{
			item->nextHitCount = countNode;
			item->prevHitCount = countNode->prevHitCount;

			BinaryNode* temp = countNode;
			temp->prevHitCount->nextHitCount = item;
			temp->prevHitCount = item;

			firstHitCountNode = item;
		}
		else if (lowerHitCount)
		{
			// set nextHitCount in item too countNode's nextHitCount //
			item->nextHitCount = countNode;
			
			// set prevHitCount in item to countNode //
			item->prevHitCount = countNode->prevHitCount;

			BinaryNode* temp = countNode;
			countNode->prevHitCount->nextHitCount = item;

			temp->prevHitCount = item;
		}
		else
		{
			// Traverse through the circular linked list //
			insertHitCount(countNode->nextHitCount, item);
		}

	}
}

BinaryNode* AVL::getMinValueItem(BinaryNode* node)
{
	BinaryNode* currNode = node;

	while (currNode->left != NULL)
	{
		currNode = currNode->left;
	}
	return currNode;
}

void AVL::remove(ItemType item)
{
	removeHitCount(firstHitCountNode, item); 
	root = remove(root, item);
}

BinaryNode* AVL::remove(BinaryNode* rootNode, ItemType item)
{
	/*
	1. Delete the Node
	*/
	if (rootNode == NULL)
	{
		return rootNode;
	}

	if (item.getName() < rootNode->item.getName())
	{
		// If the item to be deleted is smaller than the root's key, then it is from in left subtree //
		rootNode->left = remove(rootNode->left, item);
	}

	else if (item.getName() > rootNode->item.getName())
	{
		// If the item to be deleted is larger than the root's key, then it is from the right subtree
		rootNode->right = remove(rootNode->right, item);
	}
	else
	{
		// item is same as current rootNode //

		// check if the item to be deleted have one or no child //
		if ((rootNode->left == NULL) || (rootNode->right == NULL))
		{
			// determine if the child is a left leaf or right leaf //
			BinaryNode *temp = rootNode->left ? rootNode->left : rootNode->right;

			// if the item to be removed is the main root // 
			if (temp == NULL)
			{
				temp = rootNode;
				rootNode = NULL;
			}
			else
			{
				// set the child node as the new parent //
				*rootNode = *temp;
			}

			// release the memory of temp variable  //
			free(temp);
		}
		else
		{
			/*
			Case: This Item have 2 childrens
			Solution: Using inOrder traversal, find the smallest item in the right sub-tree
			*/
			BinaryNode* temp = getMinValueItem(root->right);

			// Copy the inorder successor's data to this node
			rootNode->item = temp->item;

			// Delete the inorder successor
			root->right = remove(root->right, temp->item);
		}
	}

	if (rootNode == NULL)
	{
		return rootNode;
	}

	// 2. Update the height of affected nodes //
	rootNode->height = 1 + max(getHeight(rootNode->left), getHeight(rootNode->right));

	// 3. Check if the tree is unbalanced (by Balance Factor) //
	// and make changes accordingly based on the type of unbalance tree //
	int balance = getBalance(rootNode);
	
	// Left Left Case - Perform a Right Rotation //
	if (balance > 1 && getBalance(rootNode->left) >= 0)
	{
		return rightRotate(rootNode);
	}

	// Left Right Case - Perform a Left-Right Rotation //
	if (balance > 1 && getBalance(rootNode->left) < 0)
	{
		root->left = leftRotate(rootNode->left);
		return rightRotate(rootNode);
	}

	// Right Right Case - Perform a Left Rotation //
	if (balance < -1 && getBalance(rootNode->right) <= 0)
	{
		return leftRotate(rootNode);
	}

	// Right Left Case - perform a Right-Left Rotation //
	if (balance < -1 && getBalance(rootNode->right) > 0)
	{
		root->right = rightRotate(rootNode->right);
		return leftRotate(rootNode);
	}
	
	// If the tree remained balanced //
	return rootNode;
}

void AVL::removeHitCount(BinaryNode* &countNode, ItemType item)
{
	if (firstHitCountNode->item.getName() == item.getName())
	{
		// O(1) deletion - Smallest Item //
		countNode->nextHitCount->prevHitCount = countNode->prevHitCount;
		countNode->prevHitCount->nextHitCount = countNode->nextHitCount;

		firstHitCountNode = countNode->nextHitCount;

		
	}
	else if (firstHitCountNode->prevHitCount->item.getName() == item.getName())
	{
		// O(1) deletion - Largest Item //
		BinaryNode* largestItem = countNode->prevHitCount;
		countNode->prevHitCount = largestItem->prevHitCount;
		largestItem->prevHitCount->nextHitCount = countNode;

	}
	else
	{
		// O(N) deletion //

		if (item.getName() == countNode->item.getName())
		{
			countNode->nextHitCount->prevHitCount = countNode->prevHitCount;
			countNode->prevHitCount->nextHitCount = countNode->nextHitCount;
		}
		else
		{
			removeHitCount(countNode->nextHitCount, item);
		}
	}

}

bool AVL::isEmpty()
{
	return (root == NULL);
}

void AVL::hitcountAsc()
{
	int nodes = numOfNodes(root);

	int count = 1;
	BinaryNode* copy = firstHitCountNode;
	while (count <= nodes)
	{
		Item i = copy->item;
		stringstream stream;
		stream << fixed << setprecision(2) << i.getPrice();

		cout << i.getName() << "\t\t" << i.getDescription() << setw(3) << "\t" << stream.str() << "\t" << i.getHitCount() << endl;

		copy = copy->nextHitCount;
		count++;
	}
}

void AVL::hitcountDesc()
{
	BinaryNode* copy = firstHitCountNode->prevHitCount;
	int nodes = numOfNodes(root);
	int count = 1;
	while (count <= nodes)
	{
		Item i = copy->item;
		stringstream stream;
		stream << fixed << setprecision(2) << i.getPrice();

		cout << i.getName() << "\t\t" << i.getDescription() << setw(3) << "\t" << stream.str() << "\t" << i.getHitCount() << endl;

		copy = copy->prevHitCount;
		count++;


	}
}

int AVL::numOfNodes(BinaryNode* rootNode)
{
	int count = 0;
	if (rootNode == NULL)
	{
		return 0;
	}
	
	count = 1 + numOfNodes(rootNode->left) + numOfNodes(rootNode->right);
	return count;
}

BinaryNode* AVL::rightRotate(BinaryNode* node)
{
	BinaryNode *leftNode = node->left;
	BinaryNode *leftRightNode = leftNode->right;

	// Perform rotation
	leftNode->right = node;
	node->left = leftRightNode;

	// Update heights
	node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
	leftNode->height = max(getHeight(leftNode->left), getHeight(leftNode->right)) + 1;

	// Return new root
	return leftNode;
}

BinaryNode* AVL::leftRotate(BinaryNode* node)
{
	BinaryNode *rightNode = node->right;
	BinaryNode *rightLeftNode = rightNode->left;

	// Perform rotation
	rightNode->left = node;
	node->right = rightLeftNode;

	// Update heights
	node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
	rightNode->height = max(getHeight(rightNode->left), getHeight(rightNode->right)) + 1;

	// Return new root
	return rightNode;
}

int AVL::getHeight(BinaryNode* item)
{
	if (item == NULL)
	{
		return 0;
	}
	else
	{
		return item->height;
	}
}

int AVL::getBalance(BinaryNode* node)
{
	if (node == NULL)
	{
		return 0;
	}

	return (getHeight(node->left) - getHeight(node->right));
}

void AVL::inOrder()
{
	if (isEmpty())
	{
		cout << "Tree is empty." << endl;
	}
	else
	{
		inOrder(root);
	}
}

void AVL::inOrder(BinaryNode* node)
{
	
	if (node != NULL)
	{
		inOrder(node->left);
		
		Item item = node->item;
		stringstream stream;
		stream << fixed << setprecision(2) << item.getPrice();
		
		cout << item.getName() << "\t\t" << item.getDescription() << setw(3) << "\t" << stream.str() << "\t" << item.getHitCount() << endl;

		inOrder(node->right);
	}
}

void AVL::preOrder()
{
	if (isEmpty())
		cout << "No item found" << endl;
	else
		preOrder(root);
}

void AVL::preOrder(BinaryNode* node)
{
	if (node != NULL)
	{
		Item item = node->item;
		cout << item.getName() << " ";
		preOrder(node->left);
		preOrder(node->right);
	}
}

void AVL::postOrder()
{
	if (isEmpty())
		cout << "No item found" << endl;
	else
		postOrder(root);
}

void AVL::postOrder(BinaryNode* node)
{
	if (node != NULL)
	{
		postOrder(node->left);
		postOrder(node->right);
		Item item = node->item;
		cout << item.getName() << endl;
	}
}

int AVL::max(int val1, int val2)
{
	return (val1 > val2) ? val1 : val2;
}

bool AVL::saveData(string fileName)
{

	if (isEmpty())
	{
		cout << "Tree is Empty" << endl;
	}
	else
	{
		ofstream stream(fileName);

		if (stream.fail())
		{
			cout << "Failed to open " << fileName << "." << endl;
			return false;
		}
		else
		{
			inOrderSave(root, stream);
			return true;
		}
		return false;
	}
}

void AVL::inOrderSave(BinaryNode* node, ofstream &stream)
{
	if (node != NULL)
	{
		inOrderSave(node->left, stream);

		Item item = node->item;

		stringstream sstream;
		sstream << fixed << setprecision(2) << item.getPrice();
		string price = sstream.str();
		stream << item.getName() << ";" << item.getDescription() << ";" << price << ";" << item.getHitCount() << endl;

		inOrderSave(node->right, stream);
	}
}

BinaryNode* AVL::search(string Name)
{
	BinaryNode* node = search(root, Name);
	return node;
}

BinaryNode* AVL::search(BinaryNode* node, string Name)
{
	if (node == NULL) // item not in tree
	{
		return NULL;
	}
	else
	{
		if (node->item.getName() == Name) //item is found
		{
			return node;
		}

		else
		{
			int cmp = root->item.getName().compare(node->item.getName());

			if (cmp <= 0) //search left tree
			{
				return search(node->left, Name);
			}
			else // search right tree
			{
				return search(node->right, Name);
			}
		}
	}
}
