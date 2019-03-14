class Tree {
	private:
		struct Node {
			Node* left;
			Node* right;
			Node* parent;
			int red;
			int data;
		};
		int blackheight, height, size;

		Node* search(int);
		void print_helper(Node* root, int current_depth, int target_depth);
		void balance(Node* root);
		void colorchange(Node* root);
	public:
		Tree();
		Node* root;

		void insert(int);
		void remove(int);
		void print(bool tree_output);
};