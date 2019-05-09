// Help from this page: https://www.geeksforgeeks.org/red-black-tree-set-2-insert/ on the 4 insert cases and the test sequence 7 3 18 22.... for testing tree rotation
// Lots of debugging help from this visualization: https://www.cs.usfca.edu/~galles/visualization/RedBlack.html

#include <iostream>
#include "tree.h"

//Constructor for the tree
Tree::Tree(){
	size = 0;
	root = 0;
}
//This function gets the uncle of a node, returns 0 if there is no uncle
Tree::Node* Tree::getuncle(Node* node){
	Node* parent = 0;
	if (node->parent != 0)
		parent = node->parent;
	if(node->parent->parent != 0){ //If the parent exists and the grandparent exists
		if(node->parent->parent->left == node->parent){ //If the parent is the left node
			return parent->parent->right; //Return the right node as the uncle
		}else{
			return parent->parent->left; //Otherwise the left node is the uncle
		}
	}
	return 0;
}

Tree::Node* Tree::getsibling(Node* node){
	if(node->parent == 0) return 0;
	if(on_left(node)) return node->parent->right;
	else return node->parent->left;
}

Tree::Node* Tree::search(int data){
	Node* current = root;
	while(true){
		if(current->data == data)
			return current;
		if(data > current->data)
			if(current->right != 0)
				current = current->right;
			else
				break;
		else if(data < current->data)
			if(current->left != 0)
				current = current->left;
			else
				break;
	}
	return 0;
}
//This function prints a subtree starting from a node, if you start from the root, it prints the whole tree
void Tree::print(Node* root, int current_depth){
	if(root->right != 0) //If we can go right, go right. The function goes all the way to the right of the tree first, printing it out with the right at the top, and left at the bottom
		print(root->right, current_depth + 1);
	for(int i = 0; i < current_depth; i++) //Print out a space depending on the depth of the node, so nodes that are deeper in the tree will be farther from the left of the screen
		std::cout << "   ";
	if (root->red == -1){ //If the node is red, then print it as red text
		std::cout << "\033[1;31m" << root->data << "\033[0m" << std::endl;
		/*
		std::cout << "\033[1;31m" << root->data << "(";
		if (root->parent != 0)
			std::cout << "p:" << root->parent->data << " ";
		if(root->left != 0)
			std::cout << "l:" << root->left->data << " ";
		if(root->right != 0)
			std::cout << "r:" << root->right->data;
		std::cout << ")" "\033[1;31m" << root->data <<
		*/
	}else{ //If the node is black print it as white text
		std::cout << root->data << std::endl;
		/*
		std::cout << root->data << "(";
		if (root->parent != 0)
			std::cout << "p:" << root->parent->data << " ";
		if(root->left != 0)
			std::cout << "l:" << root->left->data << " ";
		if(root->right != 0)
			std::cout << "r:" << root->right->data;
		std::cout << ")" << std::endl;
		*/
	}
	if(root->left != 0) //Go left
		print(root->left, current_depth + 1);
}
void Tree::print(Node* root, int current_depth, int search){
	if(root->right != 0) //If we can go right, go right. The function goes all the way to the right of the tree first, printing it out with the right at the top, and left at the bottom
		print(root->right, current_depth + 1, search);
	for(int i = 0; i < current_depth; i++) //Print out a space depending on the depth of the node, so nodes that are deeper in the tree will be farther from the left of the screen
		std::cout << "   ";
	if (root->red == -1){ //If the node is red, then print it as red text
		if(root->data == search)
			std::cout << "\033[1;34m" << root->data << "\033[0m" << std::endl;
		else
			std::cout << "\033[1;31m" << root->data << "\033[0m" << std::endl;
	}else{ //If the node is black print it as white text
		if(root->data == search)
			std::cout << "\033[1;34m" << root->data << "\033[0m" << std::endl;
		else
			std::cout << root->data << std::endl;
	}
	if(root->left != 0) //Go left
		print(root->left, current_depth + 1, search);
}
void Tree::rotate_left(Node* leaf){
	//Defining the nodes: parent, uncle, and grandparent in relation to the leaf node passed in
	Node* parent = leaf->parent; 
	Node* uncle = getuncle(leaf);
	Node* grandparent = 0;
	if(parent->parent != 0) grandparent = parent->parent;

	parent->parent = grandparent->parent; //Set the parent's parent to the grandparent's parent, elevating the parent to the grandparent's position
	if(grandparent->parent != 0){ //If the grandparent's parent exists
		if(grandparent->parent->right == grandparent) //Test which subtree is the grandparent is on, left or right
			grandparent->parent->right = parent; //Set its right subtree to the parent
		else
			grandparent->parent->left = parent; //Set its right subtree to the parent
	}
	if (parent->parent == 0) //If at this point the parent of the parent is 0, which was the grandparent's old parent, then the parent must be the root node
		root = parent;
	grandparent->left = parent->right; //Shift over the parents right subtree over the the grandparent's left subtree
	if(parent->right != 0)
		parent->right->parent = grandparent; //Set the parent of the parent's right subtree to the grandparent
	parent->right = grandparent; //Set the right subtree of the parent to the grandparent, now the parent should be fully elevated to the grandparent's old position(almost)
	parent->red = 1; //Make the parent black
	grandparent->parent = parent; //Set the parent of the grandparent to the parent
	grandparent->red = -1; //Make the grandparent red
}
void Tree::rotate_right(Node* leaf){
	//Defining the nodes: parent, uncle, and grandparent in relation to the leaf node passed in
	Node* parent = leaf->parent; 
	Node* uncle = getuncle(leaf);
	Node* grandparent = 0;
	if(parent->parent != 0) grandparent = parent->parent;

	parent->parent = grandparent->parent; //Set the parent's parent to the great grandparent
	if(grandparent->parent != 0){ //If the great grandparent exists
		if(grandparent->parent->right == grandparent) //Test which subtree is the grandparent is on, left or right
			grandparent->parent->right = parent; //Set its right subtree to the parent
		else
			grandparent->parent->left = parent; //Set its right subtree to the parent
	}
	if (parent->parent == 0) //If the great grandparent doesn't exist, then parent is the new root node
		root = parent;
	grandparent->right = parent->left; //Set the grandparent's right subtree to the parent's left subtree
	if(parent->left != 0)
		parent->left->parent = grandparent; //Set the parent's left subtree's parent to the grandparent
	parent->left = grandparent; //Set the parent's left subtree to the grandparent
	grandparent->parent = parent; //Set the grandparent's parent to parent
	//grandparent->left = leaf;
	grandparent->red = -1; //Make the grandparent red
	parent->red = 1; //Make the parent black
}
//This function changes the color of the node if necessary and will also rebalance it if needed.
// It's recursive and skips generations up to the root node
void Tree::balance(Node* leaf){
	//Defining the nodes: parent, uncle, and grandparent in relation to the leaf node passed in
	Node* parent = leaf->parent; 
	Node* uncle = getuncle(leaf);
	Node* grandparent = 0;
	if(parent->parent != 0) grandparent = parent->parent;

	if(parent != 0 && (parent->red != 1 || leaf != root)){ //If the parent exists and either the leaf isn't the root or the parent is red, then we're either going to change the color of nodes or balance the tree
		if(uncle != 0 && uncle->red == -1 && parent->red == -1){ //If the uncle is red and the parent is red, then we need to change the color of the nodes
			parent->red = 1; //Make the parent node black
			if(uncle != 0) //If the uncle exists, then make it black
				uncle->red = 1;
			if(grandparent != 0) //If the grandparent exists
				grandparent->red = -1; //Make it red
		}
		if(parent->red == -1 && (uncle == 0 || uncle->red == 1)){ //If the parent is red(the leaf is also red) and either the uncle doesn't exist or the uncle is black, then we need to rotate the tree.
		//When rotating the tree, there are 4 cases in which the grandparent, parent, and leaf nodes are aligned. 
			if(grandparent != 0 && grandparent->left == parent && parent->left == leaf){ //Left left case, where the parent is left of the grandparent and the leaf is left of the grandparent
				rotate_left(leaf);
				
				//Reset values since the grandparent got sifted down
				parent = leaf->parent;
				uncle = getuncle(leaf);
				if(parent->parent != 0) grandparent = parent->parent;
				
			}else if(grandparent != 0 && grandparent->left == parent && parent->right == leaf){ //Left right case, when the parent is left of the grandparent and the leaf is right of the parent
				//We essentially rotate the leaf up to the parent's position and change the tree into a left left position so we can just do left left again
				grandparent->left = leaf; //Set the grandparent's left subtree to the leaf
				leaf->parent = grandparent; //Set the parent of the leaf to the grandparent
				parent->right = leaf->left; //Set the parent's right subtree to the leaf's left subtree
				if(leaf->left != 0)
					leaf->left->parent = parent; //Set the leaf's right node's parent to parent
				leaf->left = parent; //Set the leaf's left subtree to its parent
				parent->parent = leaf; //Let the parent's parent to leaf
				//The leaf and the parent now should've switched places with no right substrees, so left left can be run successfully

				//Reset values since the parent got sifted down
				leaf = parent;

				//Repeat left left case from before
				rotate_left(leaf);
				
				//Reset values since the grandparent got sifted down
				parent = leaf->parent;
				uncle = getuncle(leaf);
				if(parent->parent != 0) grandparent = parent->parent;
			}else if(grandparent != 0 && grandparent->right == parent && parent->right == leaf){ //Right right case. This is a mirror of left left, where the parent is right of the grandparent and the leaf is right of parent
				rotate_right(leaf);

				//Reset values since the grandparent got sifted down
				parent = leaf->parent;
				uncle = getuncle(leaf);
				if(parent->parent != 0) grandparent = parent->parent;
			}else if(grandparent != 0 && grandparent->right == parent && parent->left == leaf){ //Right left case, which is a mirror of left right, and runs when the leaf is left of parent and parent is right of grandparent
				//The goal, as with left right, is to rotate the tree so that we can run right right again
				grandparent->right = leaf; //Set the grandparent's right subtree to the leaf
				leaf->parent = grandparent; //Set the leaf's parent to the grandparent
				parent->left = leaf->right; //Set the parent's left subtree to the leaf's right subtree
				if(leaf->right != 0)
					leaf->right->parent = parent; //Set the leaf's right node's parent to parent
				leaf->right = parent; //Set the leaf's right subtree to the parent
				parent->parent = leaf; //Set the parent's parent to leaf
				//Now it should look like right right

				leaf = parent;

				//Repeat right right case
				rotate_right(leaf);

				//Reset values since the grandparent got sifted down
				parent = leaf->parent;
				uncle = getuncle(leaf);
				if(parent->parent != 0) grandparent = parent->parent;
			}
		}
		if (grandparent != 0 && grandparent != root) //If the new grandparent after rotation exists and isn't the root, then recall balance for color change and further balancing
			balance(grandparent);
	}
}
Tree::Node* Tree::find_inorder(Node* current){
	if(current->left != 0)
		return find_inorder(current->left);
	else
		return current;
}
void Tree::one_child(Node* child){
	Node* leaf = child->parent;
	Node* parent = leaf->parent;
	if(parent != 0){
		if(parent->left == leaf) parent->left = child;
		else parent->right = child;
		
		child->parent = parent;
	}else{
		root = leaf->right;
		child->parent = 0;
	}
}
bool Tree::on_left(Node* node){
	return (node->parent->left == node);
}

/*
	if(leaf->left == 0 && leaf->right == 0){ //Leaf has no children
		if(leaf->data == root->data){
			delete leaf;
			return;
		}
		if(on_left(leaf))
			parent->left = 0;
		else
			parent->right = 0;
		delete leaf;
		root->red = 1;
	}else if(leaf->left == 0 && leaf->right != 0){ //Leaf has one right child
		one_child(leaf->right);
		if (leaf->right->red == -1 && parent->red == -1)
			leaf->right->red = 1;

		delete leaf;
	}else if(leaf->left != 0 && leaf->right == 0){ //Leaf has one left child
		one_child(leaf->left);

		if(leaf->left->red == -1 && parent->red == -1)
			leaf->left->red = 1;

		delete leaf;
	}else if(leaf->left != 0 && leaf->right != 0){ //Leaf has 2 children
		Node* successor = find_inorder(leaf->right);
		if(leaf->right == successor){ //Successor is the immediate right child
			successor->parent = leaf->parent;
			if(parent != 0){
				if (!on_left(leaf)) parent->right = successor;
				else parent->left = successor;
			}else{
				root = successor;
			}
			successor->left = leaf->left;
			successor->left->parent = successor;
			
			if(successor->red == 1 && successor->right != 0)
				successor->right->secondary == 1;
			successor->red = leaf->red;

			delete leaf;
		}else{ //Successor is not its child
			leaf->data = successor->data;
			if(successor->right != 0){
				successor->parent->left = successor->right;
				successor->right->parent = successor->parent;
			}
			if(successor->red == 1)
				successor->right->secondary = 1;
			successor->parent->left = 0;
			delete successor;
		}
	}
	*/

void Tree::remove(int num){
	if(root->data == num && size == 1){
		delete root;
		return;
	}
	if(search(num) == 0){
		std::cout << num << " is not in the tree" << std::endl;
		return;
	}
	Node* leaf = search(num); 
	Node* parent = leaf->parent;
	Node* child = 0;
	
	if(leaf->left == 0 && leaf->right == 0){
		child = new Node();
		child->parent = parent;
		child->data = NULL;
		child->red = NULL;

		if(leaf->red == 1)
			if(on_left(leaf)) parent->left = child;
			else parent->right = child;
		else
			if(on_left(leaf)) parent->left = 0;
			else parent->right = 0;
	}else if((leaf->left != 0 || leaf->right != 0) && (leaf->left == 0 || leaf->right == 0)){
		child = 0;
		if (leaf->right != 0) child = leaf->right;
		else child = leaf->left;

		child->parent = parent;
		if(parent != 0)
			if(on_left(leaf)) parent->left = child;
			else parent->right = child;
		else
			root = child;
	}else if(leaf->left != 0 && leaf->right != 0){
		child = find_inorder(leaf->right);
		leaf->data = child->data;
		if (leaf->right == child){
			if(child->right != 0){
				child->right->parent = leaf;
				leaf->right = child->right;
			}
			delete child;
		}else{
			if(child->right != 0){
				child->right->parent = child->parent;
				child->parent->left = child->right;
			}else{
				child->parent->left = 0;
			}
			delete child;	
		}
	}
	if(child != 0 && (leaf->red == -1 || child->red == -1)){
		child->red = 1;
	}else if(leaf->red == 1 && (child == 0 || child->red == 1 || child->red == NULL)){
		Node* sibling = getsibling(child);
		Node* rnphew = sibling->right;
		Node* lnphew = sibling->left;

		if(sibling->red == 1 && on_left(child) && (rnphew != 0 && rnphew->red == -1)){ //Right right
			Node* sparent = sibling->parent;
			sparent->right = sibling->left;
			if(sibling->left != 0)
				sibling->left->parent = sparent;
			sibling->left = sparent;
			if(sparent->parent == 0){
				root = sibling;
				sibling->parent = sparent->parent;
			}else{
				if(sparent->parent->left == sparent) sparent->parent->left = sibling;
				else sparent->parent->right = sibling;
			}
			sparent->parent = sibling;
			rnphew->red = 1;
		}else if(sibling->red == 1 && !on_left(child) && lnphew->red == -1){ //Left left
			Node* sparent = sibling->parent;
			sparent->left = sibling->right;
			sibling->right->parent = sparent;
			sibling->right = sparent;
			if(sparent->parent == 0){
				root = sibling;
				sibling->parent = sparent->parent;
			}else{
				if(sparent->parent->left == sparent) sparent->parent->left = sibling;
				else sparent->parent->right = sibling;
			}
			sparent->parent = sibling;
			lnphew->red = 1;
		}else if(sibling->red == 1 && on_left(child) && (rnphew == 0 || rnphew->red == 1)){ //Right Left
			Node* sparent = sibling->parent;
			lnphew->parent = sparent;
			sparent->right = lnphew;
			lnphew->right = sibling;
			sibling->parent = lnphew;

			lnphew->red = 1;
			sibling->red = -1;

			sibling = lnphew;
			sparent = sibling->parent;

			sparent->right = sibling->left;
			if(sibling->left != 0)
				sibling->left->parent = sparent;
			sibling->left = sparent;
			if(sparent->parent == 0){
				root = sibling;
				sibling->parent = sparent->parent;
			}else{
				if(sparent->parent->left == sparent) sparent->parent->left = sibling;
				else sparent->parent->right = sibling;
			}
			sparent->parent = sibling;
			rnphew->red = 1;
		}

		if(child->red == NULL){
			if(on_left(child)) child->parent->left = 0;
			else child->parent->right = 0;
			delete child;
		}
	}

	size--;
}
//This function handles inserting data
void Tree::insert(int data){
	if(size == 0){ //If this is the root node, set up root as a new node
		size++;
		root = new Node();
		root->data = data;
		root->parent = 0;
		root->red = 1;
		return;
	}

	Node* current = root; //Start as root, this loop will always end at where the node needs to be inserted, it cannot be infinite since the tree is finite
	while(true){ //Loop over tree
		if (data >= current->data) //Go right if the data is larger or equal to the current node
			if (current->right != 0)
				current = current->right;
			else
				break; //Leave the loop if we found the place to insert
		if (data < current->data) //Go left if the data is smaller
			if (current->left != 0)
				current = current->left;
			else
				break; //Leave if we found the place to insert
	}
	//Create a new node with the relevant information
	Node* newnode = new Node();
	newnode->data = data;
	newnode->red = -1;
	newnode->parent = current;
	if(data < current->data)
		current->left = newnode;
	if(data >= current->data)
		current->right = newnode;
	size++;
	//Balance the node and always make the root black
	balance(newnode);
	root->red = 1;
}