#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string.h>
#include "tree.h"

//Reads in a file containing numbers seperated by commas and adds them to the tree
//Format:
// 1,2,3,4,5,6
// OR
// 1,2,3,4,5,6,
void from_file(Tree* t, const char* path){
	std::ifstream file(path);
	char c;
	char token[100]; //Holds the characters
	for(int i = 0; i < sizeof(token); i++) token[i] = 0; //Fill with 0s
	int position = 0;
	while(file.get(c)){ //Loops over characters
		if(c == ','){ //When it hits a comma
			t->insert(atoi(token)); //Adds the number
			position = 0;
			for(int i = 0; i < sizeof(token); i++) token[i] = 0; //Clears the string
		}else {
			token[position] = c; //Adds the character to the string
			position++;
		}
	}
	if(strlen(token) > 0) //Adds a number at the end if the file wasn't closed with a comma
		t->insert(atoi(token));
}
int main(){
	Tree t = Tree();
	char* input = new char[10];
	while(true){
		std::cout << "Enter command(input, search, remove, print, exit): ";
		std::cin.get(input, 10);
		std::cin.clear();
		std::cin.ignore(100, '\n');

		if(strcmp(input, "input") == 0){
			std::cout << "File or Manual input(file,manual): ";
			std::cin.get(input, 10);
			std::cin.clear();
			std::cin.ignore(100, '\n');

			if(strcmp(input, "file") == 0){ //If the numbers are coming from a file
				char* filepath = new char[200];
				std::cout << "Enter path: ";
				std::cin.get(filepath, 200);
				std::cin.clear();
				std::cin.ignore(100, '\n');

				from_file(&t, filepath);
				delete[] filepath;
				t.print(t.root, 0); //Print after it adds the numbers

			}else if(strcmp(input, "manual") == 0){ //If they're being manually entered
				char* number = new char[10];
				while(true){ //Keep reading in numbers from the user as long as they're entering them
					std::cout << "Enter number(type exit to leave): ";
					std::cin >> number;
					std::cin.clear();
					std::cin.ignore(100, '\n');

					if(strcmp(number, "exit") == 0)
						break; //Leave when they type exit
					t.insert(atoi(number));
					t.print(t.root, 0); //Print after it adds them

				}
				delete[] number;
			}
		}else if(strcmp(input, "search") == 0){
			char* number = new char[10];
			std::cout << "Enter number: ";
			std:: cin >> number;
			std::cin.clear();
			std::cin.ignore(100, '\n');

			if(t.search(atoi(number)) == 0)
				std::cout << number << " doesn't exist in the tree" << std::endl;
			else{
				t.print(t.root, 0, atoi(number));
			}
			delete[] number;
		}else if(strcmp(input, "remove") == 0){
			char* number = new char[10];
			std::cout << "Enter number: ";
			std:: cin >> number;
			std::cin.clear();
			std::cin.ignore(100, '\n');

			t.remove(atoi(number));
			delete[] number;
			t.print(t.root, 0);
		}else if(strcmp(input, "exit") == 0){
			break; //Leave when they type exit
		}else if(strcmp(input, "print") == 0){
			t.print(t.root, 0); //Print the tree from the root
		}else{
			std::cout << "Not sure what that command is..." << std::endl;
		}
	}
	delete[] input;
	return 0;
}