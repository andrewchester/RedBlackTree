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
		void balance(Node*);
		Node* getuncle(Node* node);
	public:
		Tree();
		Node* root;

		void insert(int);
		void remove(int);
		void print(Node*, int);
};