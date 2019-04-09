#include <iostream>
#include <windows.h>
#include "tree.h"

Tree::Tree(){
	size = 0;
	root = 0;
	blackheight = 0;
	height = 0;
}
void Tree::shift(Node* node){
	Node* parent = node->parent;
	Node* opposite = 0;
	if(parent->left == node){
		opposite = parent->right;
		parent->left = opposite;
		parent->right = node;
	}else{
		opposite = parent->left;
		parent->right = opposite;
		parent->right = node;
	}
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
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if(root->right != 0)
		print(root->right, current_depth + 1);
	for(int i = 0; i < current_depth; i++)
		std::cout << "     ";
	if (root->red == -1){
		SetConsoleTextAttribute(hConsole, 12);
		std::cout << root->data << std::endl;
		SetConsoleTextAttribute(hConsole, 15);
	}else{
		std::cout << root->data << std::endl;
	}
	if(root->left != 0)
		print(root->left, current_depth + 1);
}

void Tree::colorchange(Node* leaf){
	Node* parent = leaf->parent;
	Node* uncle = getuncle(leaf);
	
	if (parent != 0){
		if (leaf->red == parent->red){
			if(parent != 0)
				parent->red *= -1;
			if (uncle != 0){
				if(uncle->left != 0 && uncle->red == uncle->left->red)
					uncle->red *= -1;	
				if(uncle->right != 0 && uncle->red == uncle->right->red)
					uncle->red *= -1;
				if(uncle->left == 0 && uncle->right == 0)
					uncle->red *= -1;
			}
			colorchange(parent);
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

				if(newnode->parent->red == newnode->red){
					if(newnode->parent->left == newnode && newnode->parent->right == 0){
						Node* grandparent = newnode->parent->parent;
						Node* parent = newnode->parent;

						if(grandparent->parent != 0)
							parent->parent = grandparent->parent;
						else
							parent->parent = 0;
						
						parent->right = grandparent;
					}
				}
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
				
				if(newnode->parent->red == newnode->red){
					if(newnode->parent->left == newnode && newnode->parent->right == 0){
						Node* grandparent = newnode->parent->parent;
						Node* parent = newnode->parent;

						parent->right = grandparent;
						parent->parent = grandparent->parent;
						if(grandparent->parent != 0 && grandparent->parent->left == grandparent)
							grandparent->parent->left = parent;
						else if(grandparent->parent != 0)
							grandparent->parent->right = parent;
						grandparent->parent = parent;
					}
				}
				if(newnode->parent->red == -1)
					colorchange(newnode);
				root->red = 1;
				break;
			}
	}

}