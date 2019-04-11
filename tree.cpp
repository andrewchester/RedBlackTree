#include <iostream>
#include "tree.h"

Tree::Tree(){
	size = 0;
	root = 0;
	blackheight = 0;
	height = 0;
}
Tree::Node* Tree::getuncle(Node* node){
	if(node->parent != 0 && node->parent->parent != 0){
		if (node->parent->parent->left == node->parent){
			return node->parent->parent->right;
		}else{
			return node->parent->parent->left;
		}
	}
	return 0;
}


void Tree::print(Node* root, int current_depth){
	if(root->right != 0)
		print(root->right, current_depth + 1);
	for(int i = 0; i < current_depth; i++)
		std::cout << "     ";
	if (root->red == -1){
		std::cout << "\033[1;31m" << root->data << "\033[0m" << std::endl;
	}else{
		std::cout << root->data << std::endl;
	}
	if(root->left != 0)
		print(root->left, current_depth + 1);
}

void Tree::balance(Node* leaf){
	Node* parent = leaf->parent;
	Node* uncle = getuncle(leaf);
	Node* grandparent = 0;
	if(parent->parent != 0) grandparent = parent->parent;

	if(parent != 0 && (parent->red != 1 || leaf != root)){
		if(uncle != 0 && uncle->red == -1){
			parent->red = 1;
			if(uncle != 0)
				uncle->red = 1;
			if(grandparent != 0){
				grandparent->red = -1;
				if (grandparent != root)
					balance(grandparent);
			}
		}
		if(uncle == 0 || uncle->red == 1){
			if(grandparent != 0 && grandparent->left == parent && parent->left == leaf){ //Left left case
				parent->parent = grandparent->parent;
				if (parent->parent == 0)
					root = parent;
				parent->right = grandparent;
				grandparent->parent = parent;
				grandparent->left = 0;
				grandparent->red = -1;
			}else if(grandparent != 0 && grandparent->left == parent && parent->right == leaf){ //Left right case
				grandparent->left = leaf;
				leaf->left = parent;
				leaf->right = 0;
				leaf->parent = grandparent;
				parent->left = 0;
				parent->right = 0;
				parent->parent = leaf;

				//Repeat left left case
				parent->parent = grandparent->parent;
				if (parent->parent == 0)
					root = parent;
				parent->right = grandparent;
				grandparent->parent = parent;
				grandparent->left = 0;
				grandparent->red = -1;
			}else if(grandparent != 0 && grandparent->right == parent && parent->right == leaf){ //Right right case
				parent->parent = grandparent->parent;
				if (parent->parent == 0)
					root = parent;
				parent->left = grandparent;
				grandparent->parent = parent;
				grandparent->right = 0;
				grandparent->red = -1;
			}else if(grandparent != 0 && grandparent->right == parent && parent->left == leaf){ //Right left case
				grandparent->right = leaf;
				leaf->right = parent;
				leaf->left = 0;
				leaf->parent = grandparent;
				parent->left = 0;
				parent->right = 0;
				parent->parent = leaf;

				//Mirror right right case
				parent->parent = grandparent->parent;
				if (parent->parent == 0)
					root = parent;
				parent->left = grandparent;
				grandparent->parent = parent;
				grandparent->right = 0;
				grandparent->red = -1;
			}
		}
	}
}

void Tree::insert(int data){
	if(size == 0){
		size++;
		height++;
		root = new Node();
		root->data = data;
		root->parent = 0;
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
				
				balance(newnode);
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
				
				balance(newnode);
				root->red = 1;
				break;
			}
	}

}