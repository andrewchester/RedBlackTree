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
	t.insert(1);
	t.print(t.root, 0);

	return 0;
}