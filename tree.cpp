#include <iostream>
#include <windows.h>
#include "tree.h"

Tree::Tree(){
	size = 0;
	root = 0;
	blackheight = 0;
	height = 0;
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
	Node* uncle = 0;
	
	if(parent != 0 && parent->parent != 0){
		if (parent->parent->left == parent){
			uncle = parent->parent->right;
		}else{
			uncle = parent->parent->left;
		}
	}
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