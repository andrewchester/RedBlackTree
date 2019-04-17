class Tree {
	private:
		struct Node { //Struct for the node, holds it's color value, data, and the adjacent nodes
			Node* left;
			Node* right;
			Node* parent;
			int red;
			int data;
		};

		int blackheight, height, size;

		void rotate_right(Node* leaf);
		void rotate_left(Node* leaf);

		Node* find_inorder(Node* node,int, int);
		void balance(Node*); //Balances and recolors a tree from a given node
		Node* getuncle(Node* node); //Returns the uncle of a node
	public:
		Tree();
		Node* root; //Root of tree

		void insert(int); //Inserts an integer into the tree
		void remove(int); //Removes an integer from the tree if it exists - unimplemented
		Node* search(int); //Searches the tree for a value - unimplemented
		void print(Node*, int); //Prints the tree
		void print(Node*, int, int); //Prints the tree with the searched for node in blue
};