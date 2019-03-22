#include <iostream>
#include "tree.h"

Tree::Tree(){
	size = 0;
	root = 0;
	blackheight = 0;
	height = 0;
}
void Tree::countchildren(Node* root, int* count){
	(*count)++;
	if(root->left != 0) countchildren(root->left, count);
	if(root->right != 0) countchildren(root->right, count);
}
void Tree::print(Node* root, int current_depth){
	if(root->right != 0)
		print(root->right, current_depth + 1);
	for(int i = 0; i < current_depth; i++)
		std::cout << "     ";
	std::cout << root->data * root->red << std::endl;
	if(root->left != 0)
		print(root->left, current_depth + 1);
}

void Tree::colorchange(Node* leaf){
	Node* grandfather;
	Node* uncle;
	if (leaf->parent != 0 && leaf->parent->parent != 0)
		grandfather = leaf->parent->parent;
	else
		return;
	if (grandfather->left == leaf->parent)
		uncle = grandfather->right;
	else
		uncle = grandfather->left;
	leaf->parent->red *= -1;
	int* count = new int;
	*count = 0;
	countchildren(uncle, count);
	if(uncle != 0 && *count > 2)
		uncle->red *= -1;
	delete count;
	colorchange(leaf->parent);
}

void Tree::insert(int data){
	if(size == 0){
		size++;
		height++;
		root = new Node();
		root->data = data;
		root->red = 1;
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
				newnode->red = -1;
				newnode->parent = current;
				current->right = newnode;
				size++;
				
				if(newnode->parent->red == -1)
					colorchange(newnode);
				root->red = 1;
				break;
			}
		if (data < current->data)
			if (current->left != 0)
				current = current->left;
			else{
				Node* newnode = new Node();
				newnode->data = data;
				newnode->red = -1;
				newnode->parent = current;
				current->left = newnode;
				size++;
				
				if(newnode->parent->red == -1)
					colorchange(newnode);
				root->red = 1;
				break;
			}
	}

}