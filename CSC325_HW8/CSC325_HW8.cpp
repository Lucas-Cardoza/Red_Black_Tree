//********************************************************************
//
// Student: Lucas Cardoza
// Course: CSC 325: Algorithms & Advanced Data Structures
// Project #8
// Due Date: Wednesday, December 2, 2020, 1:00 PM
// Instructor: Dr. Yang Wang
//
//********************************************************************


#include "RBTree.h"


int main()
{
	RBTree rbt;			// Create instance of RB Tree
	bool quit = false;	// While loop controller
	std::string option, number;	// Variables for user input
	int key{ 0 };		// Variable for user input

	while (!quit)
	{
		std::cout << "\nProgram options are: \no = output \ns = search \ni = insert \nd = delete";
		std::cout << "\nw = walk the tree \nc = successor \ne = predecessor \nq = quit program" << std::endl;
		std::cout << "\nPlease enter your option of choice: ";
		std::cin >> option;

		if (option.length() > 1)
		{
			option = '0'; // Set user input to an invalid input to trigger an invalid input response
		}

		switch (option[0])
		{
		case 'o':	// Option to display RB Tree
		{
			std::cout << std::endl;
			rbt.displayTree();	// Call to display RB Tree
			break;
		}
		case 's':	// Option to search RB Tree for a number
		{
			std::cout << "\nPlease enter number to be searched for: ";
			std::cin >> number;
			key = stoi(number);		// Convert string to an int
			NodePtr node = rbt.searchTree(key);	// Get node of number searched for
			int parentKey{ 0 };		// Variable to set parent key of node searched for

			if (!node)	// Check to see if node is valid or not
			{
				std::cout << "\n" << number << " could not be found." << std::endl;
			}
			else if (!node->parent->key)	// Check to see if node is root node
			{
				std::cout << "\n" << key << " is the root node." << std::endl;
			}
			else if (node->parent->left->key == key)	// Check to see if node is left of parent
			{
				parentKey = node->parent->key;
				std::cout << "\n" << key << " is the left child of node " << parentKey << "." << std::endl;
			}
			else if (node->parent->right->key == key)	// Check to see if node is right of parent
			{
				parentKey = node->parent->key;
				std::cout << "\n" << key << " is the right child of node " << parentKey << "." << std::endl;
			}
			
			break;
		}
		case 'i':	// Option to insert a number into RB Tree
		{
			std::cout << "\nPlease enter the number to be placed into the RB Tree: ";
			std::cin >> number;
			key = std::stoi(number);	// Convert string to an int
			rbt.RBT_Insert(key);		// Call to insert number into RB Tree
			std::cout << std::endl;
			rbt.displayTree();			// Call to display RB Tree
			break;
		}
		case 'd':	// Option to delete a number from the RB Tree
		{
			std::cout << "\nPlease enter the number to be deleted from the RB Tree: ";
			std::cin >> number;
			key = std::stoi(number);	// Convert string to an int
			rbt.deleteNode(key);		// Call to delete number from RB Tree
			std::cout << std::endl;
			rbt.displayTree();			// Call to display RB Tree
			break;
		}
		case 'w':	// Option to use walk through RB Tree methods
		{
			bool walk = true;	// While loop controller
			std::string order;	// Variable for user input

			while (walk)
			{
				std::cout << "\nWhich walk would you like? \nl = in-order \np = pre-order \nt = post-order \nb = back to main menu " << std::endl;
				std::cout << "\nPlease enter your walk of choice: ";
				std::cin >> order;

				if (order.length() > 1)
				{
					order = '0'; // Set user input to an invalid input to trigger an invalid input response
				}

				switch (order[0])
				{
				case 'l':	// Option to use in-order walk-through
				{
					std::cout << "\n";
					rbt.tree_walk(1);	// Call to use in-order walk
					std::cout << std::endl;
					break;
				}
				case 'p':	// Option to use pre-order walk-through
				{
					std::cout << "\n";
					rbt.tree_walk(2);	// Call to use pre-order walk
					std::cout << std::endl;
					break;
				}
				case 't':	// Option to use post-order walk-through
				{
					std::cout << "\n";
					rbt.tree_walk(3);	// Call to use post-order walk
					std::cout << std::endl;
					break;
				}
				case 'b':	// Option to return to main menu
				{
					walk = false;
					break;
				}
				default:	// Invalid user input case
				{
					std::cout << "\n" << "Input is not a valid option." << std::endl;
					break;
				}
				}
			}

			break;
		}
		case 'c':	// Option to find successor
		{
			std::cout << "\nPlease enter number to find successor: ";
			std::cin >> number;
			key = stoi(number);		// Convert string to an int
			NodePtr node = rbt.searchTree(key);	// Get node of number searched for
			NodePtr successor = rbt.Tree_Successor(node);	// Call to find successor node
			int suc = successor->key;

			// Check to see if node is a leaf node of RB Tree
			if (!successor->left)
			{
				int suc = successor->key;
				std::cout << "\n" << key << " has no successor." << std::endl;
				break;
			}
			else
			{
				std::cout << "\nThe successor to " << key << " is: " << suc << "." << std::endl;
				break;
			}
		}
		case 'e':	// Option to find predecessor
		{
			std::cout << "\nPlease enter number to find predecessor: ";
			std::cin >> number;
			key = stoi(number);		// Convert string to an int
			NodePtr node = rbt.searchTree(key);	// Get node of number searched for
			NodePtr predecessor = rbt.Tree_Predecessor(node);	// Call to find predecessor node
			int pred = predecessor->key;

			// Check to see if node is the root node of RB Tree
			if (!predecessor->parent)
			{
				std::cout << "\n" << key << " has no predecessor." << std::endl;
				break;
			}
			else
			{
				std::cout << "\nThe predecessor to " << key << " is: " << pred << "." << std::endl;
				break;
			}
		}
		case 'q':	// Option to quit the program
		{
			std::cout << "\nExiting program." << std::endl;
			quit = true;
			break;
		}

		default:	// Invalid user input case
		{
			std::cout << "\n" << "Input is not a valid option." << std::endl;
			break;
		}
		}
	}

	return 0;
}