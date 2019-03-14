#include <iostream>
#include "tree.h"

int main(){
	Tree t = Tree();
	t.insert(10);
	t.insert(5);
	t.insert(15);
	t.insert(20);
	t.insert(7);
	t.insert(3);
	t.print(true);

	return 0;
}