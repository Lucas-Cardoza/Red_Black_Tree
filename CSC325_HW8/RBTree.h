//********************************************************************
//
// Student: Lucas Cardoza
// Course: CSC 325: Algorithms & Advanced Data Structures
// Project #8
// Due Date: Wednesday, December 2, 2020, 1:00 PM
// Instructor: Dr. Yang Wang
//
//********************************************************************


#ifndef _RBTree_
#define _RBTree_

#include <string>
#include <iostream>


struct Node	// Structure of nodes
{
	int key = 0;
	Node* parent = nullptr;
	Node* left = nullptr;
	Node* right = nullptr;
	std::string color = "Black";
};


typedef Node* NodePtr;	// Define a node pointer for ease of use throughout program


class RBTree	// Class for RB Tree and function prototypes
{
private:
	NodePtr root;
	NodePtr nil;
	void Left_Rotate(NodePtr);
	void Right_Rotate(NodePtr);
	void RB_Transplant(NodePtr, NodePtr);
	void RB_Delete_Fixup(NodePtr);
	NodePtr Tree_Minimum(NodePtr);
	NodePtr Tree_Maximum(NodePtr);
	NodePtr RBT_Search(NodePtr, int);
	void InOrder_Tree_Walk(NodePtr);
	void PreOrder_Tree_Walk(NodePtr);
	void PostOrder_Tree_Walk(NodePtr);
	void RBT_Delete(NodePtr, int);
	void RBT_Output(NodePtr, std::string, bool);
	void RBT_Insert_Fixup(NodePtr);

	void initializeNode(NodePtr node, NodePtr parent)
	{
		node->key = 0;
		node->parent = nullptr;
		node->left = nullptr;
		node->right = nullptr;
		node->color = "Black";
	}

public:
	RBTree()
	{
		nil = new Node;
		nil->key = 0;
		nil->left = nullptr;
		nil->right = nullptr;
		root = nil;
	}

	NodePtr getRoot();
	void RBT_Insert(int);
	void displayTree();
	void deleteNode(int);
	void tree_walk(int);
	NodePtr searchTree(int);
	NodePtr Tree_Successor(NodePtr);
	NodePtr Tree_Predecessor(NodePtr);
	~RBTree();
};


#endif 

