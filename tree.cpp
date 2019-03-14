#include <iostream>
#include "tree.h"

Tree::Tree(){
	size = 0;
	root = 0;
	blackheight = 0;
	height = 0;
}

void Tree::print_helper(Node* root, int current_depth, int target_depth){
	if(current_depth > target_depth) //If we're too deep into the tree, return
		return;
	if(current_depth == target_depth){ //If this is the right depth, then print out the data of the node
		if (root->parent != 0){
			std::cout << root->data * root->red << "(" << root->parent->data << ") ";
		}else{
			std::cout << root->data * root->red << " ";
		}
		return;
	}
	if(current_depth < target_depth){ //If we need to go deeper
		if(root->left != 0) //Make sure left exists
			print_helper(root->left, current_depth + 1, target_depth); //Go down the left side
		if(root->right != 0) //Make sure right exists
			print_helper(root->right, current_depth + 1, target_depth); //Go down the right side
	}
}

void Tree::print(bool tree_output){
	if(size == 0)
		return;
	std::cout << "format: data(parent)" << std::endl;
	int width = 1, tsize = size, total_depth = 1; //Declare the width, which is the current width of the tree at that depth, the size, which is the size of the tree, and the depth, which should be the depth of the tree
	while(tsize > width){ //When the width is greater than size, we're not at the bottom 
		tsize -= width; //Decrease size as we go further down
		width *= 2; //Calculate the total width of how many nodes should be at this depth when full
		total_depth++; //Increases the depth each time we go down
	}
	if(tree_output){
		int print_depth = 1; //The current depth of the heap we're printing
		width = 1; //Current width of the print depth
		while(print_depth <= total_depth){ 
			print_helper(root, 1, print_depth); //Prints out all nodes in the heap at the right depth
			std::cout << std::endl; 
			width *= 2; //Increase the width of the tree
			print_depth++; //Increase the print depth
		}
	}else{
		for(int i = 1; i <= total_depth; i++) //Loop through the layers and output it all in one go
			print_helper(root, 1, i);
		std::cout << std::endl;
	}
}

void Tree::colorchange(Node* root){
	if(root->left == 0 && root->right == 0)
		root->red = 1;
	if(root->left->red == 1){
		root->red = -1;
	}else{
		root->red = 1;
	}
	if (root == this->root)
		root->red = -1;
	if (root->parent != 0)
		colorchange(root->parent);
}

void Tree::insert(int data){
	if(size == 0){
		size++;
		height++;
		root = new Node();
		root->data = data;
		root->red = -1;
		return;
	}

	Node* current = root;
	int depth = 1;
	while(true){
		if (data >= current->data)
			if (current->right != 0)
				current = current->right;
			else{
				Node* newnode = new Node();
				newnode->data = data;
				newnode->red = 1;
				newnode->parent = current;
				current->right = newnode;
				size++;

				colorchange(newnode);
				break;
			}
		if (data < current->data)
			if (current->left != 0)
				current = current->left;
			else{
				Node* newnode = new Node();
				newnode->data = data;
				newnode->red = 1;
				newnode->parent = current;
				current->left = newnode;
				size++;

				colorchange(newnode);
				break;
			}
	}

}