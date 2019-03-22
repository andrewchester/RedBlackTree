#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string.h>
#include "tree.h"

void from_file(Tree* t, const char* path){
	std::ifstream file(path);
	char c;
	char token[100];
	for(int i = 0; i < sizeof(token); i++) token[i] = 0;
	int position = 0;
	while(file.get(c)){
		if(c == ' '){
			t->insert(atoi(token));
			position = 0;
			for(int i = 0; i < sizeof(token); i++) token[i] = 0;
		}else {
			token[position] = c;
			position++;
		}
	}
}
int main(){
	Tree t = Tree();
	char* input = new char[10];
	while(true){
		std::cout << "Enter command(input, exit, print): ";
		std::cin.get(input, 10);
		std::cin.clear();
		std::cin.ignore(100, '\n');

		if(strcmp(input, "input") == 0){
			std::cout << "File or Manual input(file,manual): ";
			std::cin.get(input, 10);
			std::cin.clear();
			std::cin.ignore(100, '\n');

			if(strcmp(input, "file") == 0){
				char* filepath = new char[200];
				std::cout << "Enter path: ";
				std::cin.get(filepath, 200);
				std::cin.clear();
				std::cin.ignore(100, '\n');

				from_file(&t, filepath);
				delete[] filepath;
			}else if(strcmp(input, "manual") == 0){
				char* number = new char[10];
				while(true){
					std::cout << "Enter number(type exit to leave): ";
					std::cin >> number;
					std::cin.clear();
					std::cin.ignore(100, '\n');

					if(strcmp(number, "exit") == 0)
						break;
					t.insert(atoi(number));
					t.print(t.root, 0);
				}
				delete[] number;
			}
		}else if(strcmp(input, "exit") == 0){
			break;
		}else if(strcmp(input, "print") == 0){
			t.print(t.root, 0);
		}else{
			std::cout << "Not sure what that command is..." << std::endl;
		}
	}
	delete[] input;
	return 0;

	return 0;
}