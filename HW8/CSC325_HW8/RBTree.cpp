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


// Function to return the root node of RB Tree to calling function
NodePtr RBTree::getRoot()   
{
    return this->root;
}


// Function to insert user defined number into RB Tree
void RBTree::RBT_Insert(int key)    
{
    // Initialize new node for user defined number
    NodePtr node = new Node;
    node->key = key;
    node->parent = nullptr;
    node->left = nil;
    node->right = nil;
    node->color = "Red";

    NodePtr y = nil;    // Node pointer for parent node of new node
    NodePtr x = this->root;     // Root node of tree

    // Check for location in RB Tree to insert new node
    while (x != nil)
    {
        y = x;

        if (node->key == x->key)
        {
            std::cout << "\n" << key << " node is already in the tree." << std::endl;
            return;
        }
        else if (node->key < x->key)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }

    // Assign node y to be parent node of new node
    node->parent = y;   

    // Decide if new node should be left or right child of node y
    if (y == nil)   // node y is above the root node (out of scope)
    {
        root = node;    // Make new node root in this case
    }
    else if (node->key < y->key)
    {
        y->left = node;     // Make new node left child of node y
    }
    else
    {
        y->right = node;    // Make new node right child of node y
    }

    node->left = nil;   // Set left leaf node
    node->right = nil;  // Set right leaf node
    node->color = "Red";    // Set color of new node
    RBT_Insert_Fixup(node); // Call to correct R&B properties after new node insertion
}


// Function to correct R&B properties of nodes
void RBTree::RBT_Insert_Fixup(NodePtr node)
{
    NodePtr y = nil;

    // node = new node which was inserted into RB Tree
    while (node->parent->color == "Red")
    {
        if (node->parent == node->parent->parent->left)
        {
            y = node->parent->parent->right;

            if (y->color == "Red")
            {
                node->parent->color = "Black";
                y->color = "Black";
                node->parent->parent->color = "Red";
                node = node->parent->parent;
            }
            else
            {
                if (node == node->parent->right)
                {
                    node = node->parent;
                    Left_Rotate(node);
                }

                node->parent->color = "Black";
                node->parent->parent->color = "Red";
                // Call to rotate RB Tree right to correct tree
                Right_Rotate(node->parent->parent);
            }
        }
        else
        {
            y = node->parent->parent->left;

            if (!y)
            {
                break;
            }

            if (y->color == "Red")
            {
                node->parent->color = "Black";
                y->color = "Black";
                node->parent->parent->color = "Red";
                node = node->parent->parent;
            }
            else
            {
                if (node == node->parent->left)
                {
                    node = node->parent;
                    Right_Rotate(node);
                }

                node->parent->color = "Black";
                node->parent->parent->color = "Red";
                // Call to rotate RB Tree left to correct tree
                Left_Rotate(node->parent->parent);
            }
        }

        if (node == root) // No rotations needed
        {
            break;
        }
    }

    root->color = "Black";
}


// Function to rotate RB Tree left for corrections to R&B properties
void RBTree::Left_Rotate(NodePtr node)
{
    NodePtr y = node->right;
    node->right = y->left;

    if (y->left != nil)
    {
        y->left->parent = node;
    }

    y->parent = node->parent;

    if (node->parent == nil)
    {
        root = y;
    }
    else if (node == node->parent->left)
    {
        node->parent->left = y;
    }
    else
    {
        node->parent->right = y;
    }

    y->left = node;
    node->parent = y;
}


// Function to rotate RB Tree right for corrections to R&B properties
void RBTree::Right_Rotate(NodePtr node)
{
    NodePtr y = node->left;
    node->left = y->right;

    if (y->right != nil)
    {
        y->right->parent = node;
    }

    y->parent = node->parent;

    if (node->parent == nil)
    {
        root = y;
    }
    else if (node == node->parent->right)
    {
        node->parent->right = y;
    }
    else
    {
        node->parent->left = y;
    }

    y->right = node;
    node->parent = y;
}


// Function to make calls to print RB Tree
void RBTree::displayTree()
{
    if (root) // If there is a root, start print out from there.
    {
        // Call to traverse through RB Tree and print data to screen
        RBT_Output(this->root, "", true);   
    }

    if (root == nil)    // If root node is empty, the tree is empty
    {
        std::cout << "The tree is empty" << std::endl;
    }
}


// Function to traverse through RB Tree and print data to screen
void RBTree::RBT_Output(NodePtr node, std::string spacing, bool last)
{
    // If node is not empty, print node data
    if (node != nil)    
    {
        std::cout << spacing;

        if (spacing.length() == 0)  // Check for root node
        {
            std::cout << "Root---- ";
            spacing += "         ";
        }
        else if (last)
        {
            std::cout << "R---- ";
            spacing += "      ";
        }
        else
        {
            std::cout << "L---- ";
            spacing += "|     ";
        }

        std::string color = node->color; // Set color variable to color of node for print out

        std::cout << node->key << " (" << color << ")" << std::endl;
        // Recursive calls to left and right nodes to continue to print RB Tree data 
        RBT_Output(node->left, spacing, false);
        RBT_Output(node->right, spacing, true);
    }
}


// Function to make search through RB Tree call
NodePtr RBTree::searchTree(int key)
{
    return RBT_Search(this->root, key);
}


// Function to search through RB Tree to find node of user requested number
NodePtr RBTree::RBT_Search(NodePtr node, int key)
{
    // Check if requested node is root node
    if (node == NULL || key == node->key)
    {
        return node;
    }

    // If requested node is not root node, recursively check left or right nodes
    if (key < node->key)
    {
        return RBT_Search(node->left, key);  // Check left node
    }
    else
    {
        return RBT_Search(node->right, key); // Check right node
    }
}


// Function for RB Tree walk through requests
void RBTree::tree_walk(int order)
{
    // Call to get root node from RB Tree
    NodePtr root = getRoot();

    switch (order)
    {
    case 1:
    {
        // Call to make in-order walk through RB Tree
        InOrder_Tree_Walk(root);
        break;
    }
    case 2:
    {
        // Call to make pre-order walk through RB Tree
        PreOrder_Tree_Walk(root);
        break;
    }
    case 3:
    {
        // Call to make post-order walk through RB Tree
        PostOrder_Tree_Walk(root);
        break;
    }
    default:
        break;
    }
}


// Function for in-order walk
void RBTree::InOrder_Tree_Walk(NodePtr node)
{
    if (node != nil)
    {
        // Recursive calls to in-order function
        InOrder_Tree_Walk(node->left);
        std::cout << node->key << " ";
        InOrder_Tree_Walk(node->right);
    }
}


// Function for pre-order walk
void RBTree::PreOrder_Tree_Walk(NodePtr node)
{
    if (node != nil)
    {
        std::cout << node->key << " ";
        // Recursive calls to pre-order function
        PreOrder_Tree_Walk(node->left);
        PreOrder_Tree_Walk(node->right);
    }
}


// Function for post-order walk
void RBTree::PostOrder_Tree_Walk(NodePtr node)
{
    if (node != nil)
    {
        // Recursive calls to post-order function
        PostOrder_Tree_Walk(node->left);
        PostOrder_Tree_Walk(node->right);
        std::cout << node->key << " ";
    }
}

// Function for tree successor. Not used for this assignment, but I decided I may try using it later.
NodePtr RBTree::Tree_Successor(NodePtr node)
{
    if (node->right != nil)
    {
        return Tree_Minimum(node->right);
    }

    NodePtr y = node->parent;

    while (y != nil && node == y->right)
    {
        node = y;
        y = y->parent;
    }
    return y;
}


// Function for tree predecessor. Not used for this assignment, but I decided I may try using it later.
NodePtr RBTree::Tree_Predecessor(NodePtr node)
{
    if (node->left != nil)
    {
        return Tree_Maximum(node->left);
    }

    NodePtr y = node->parent;

    while (y != nil && node == y->left)
    {
        node = y;
        y = y->parent;
    }

    return y;
}


// Function to make call to delete node
void RBTree::deleteNode(int key)
{
    RBT_Delete(this->root, key);
}


// Function to remove user defined node (key) from BR Tree
void RBTree::RBT_Delete(NodePtr root, int key)
{
    NodePtr nodeToRemove = nil;
    NodePtr y = nullptr, x = nullptr; // Temporary node pointers to use during node removal

    // Looking through the RB Tree for the node with the requested node
    while (root != nil)
    {
        if (root->key == key)   // Node was found
        {
            nodeToRemove = root;
        }
        
        if (root->key <= key)   // Look through right nodes
        {
            root = root->right;
        }
        else    // Look through left nodes
        {
            root = root->left;
        }
    }

    // If the node could not be found, display so
    if (nodeToRemove == nil)
    {
        std::cout << "\n" << key << " could not be found in the tree." << std::endl;
        return;
    }

    // If the node was found do the following
    y = nodeToRemove;
    std::string y_original_color = y->color;

    if (nodeToRemove->left == nil)
    {
        x = nodeToRemove->right;
        // Call to transplant node with another node
        RB_Transplant(nodeToRemove, nodeToRemove->right);
    }
    else if (nodeToRemove->right == nil)
    {
        x = nodeToRemove->left;
        // Call to transplant node with another node
        RB_Transplant(nodeToRemove, nodeToRemove->left);
    }
    else
    {
        // Find a node with lower value than current node
        y = Tree_Minimum(nodeToRemove->right);
        y_original_color = y->color;
        x = y->right;

        if (y->parent == nodeToRemove)
        {
            x->parent = y;
        }
        else
        {
            // Call to transplant node with another node
            RB_Transplant(y, y->right);
            y->right = nodeToRemove->right;
            y->right->parent = y;
        }

        // Call to transplant node with another node
        RB_Transplant(nodeToRemove, y);
        y->left = nodeToRemove->left;
        y->left->parent = y;
        y->color = nodeToRemove->color;

        // Remove requested node from RB Tree
        delete nodeToRemove;

        if (y_original_color == "Black")
        {
            // Call to correct RB Tree after a node removal
            RB_Delete_Fixup(x);
        }
    }
}


// Function to swap one subtree with another
void RBTree::RB_Transplant(NodePtr nodeOne, NodePtr nodeTwo)
{
    if (nodeOne->parent == nil)
    {
        root = nodeTwo;
    }
    else if (nodeOne == nodeOne->parent->left)
    {
        nodeOne->parent->left = nodeTwo;
    }
    else
    {
        nodeOne->parent->right = nodeTwo;
    }

    nodeTwo->parent = nodeOne->parent;
}


// Function to correct R&B properties after a node has been removed 
void RBTree::RB_Delete_Fixup(NodePtr node)
{
    NodePtr w = NULL;

    while (node != root && node->color == "Black")
    {
        if (node == node->parent->left)
        {
            w = node->parent->right;

            if (w->color == "Red")
            {
                w->color = "Black";
                node->parent->color = "Red";
                Left_Rotate(node->parent);
                w = node->parent->right;
            }

            if (w->left->color == "Black" && w->right->color == "Black")
            {
                w->color = "Red";
                node = node->parent;
            }
            else if (w->right->color == "Black")
            {
                w->left->color = "Black";
                w->color = "Red";
                Right_Rotate(w);
                w = node->parent->right;
            }

            w->color = node->parent->color;
            node->parent->color = "Black";
            w->right->color = "Black";
            Left_Rotate(node->parent);
            node = root;
        }
        else
        {
            w = node->parent->left;

            if (w->color == "Red")
            {
                w->color = "Black";
                node->parent->color = "Red";
                Right_Rotate(node->parent);
                w = node->parent->left;
            }

            if (w->right->color == "Black" && w->left->color == "Black")
            {
                w->color = "Red";
                node = node->parent;
            }
            else if (w->left->color == "Black")
            {
                w->right->color = "Black";
                w->color = "Red";
                Left_Rotate(w);
                w = node->parent->left;
            }

            w->color = node->parent->color;
            node->parent->color = "Black";
            w->left->color = "Black";
            Right_Rotate(node->parent);
            node = root;
        }

        node->color = "Black";
    }
}


// Function to find the minimum element in the RB Tree
NodePtr RBTree::Tree_Minimum(NodePtr node)
{
    while (node->left != nil)
    {
        node = node->left;
    }

    return node;
}


// Function to find the maximum element in the RB Tree
NodePtr RBTree::Tree_Maximum(NodePtr node)
{
    while (node->right != nil)
    {
        node = node->right;
    }
    return node;
}


// Destructor Function
RBTree::~RBTree() {}















