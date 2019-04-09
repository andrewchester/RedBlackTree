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
		void balance(Node* root);
		void colorchange(Node*);
		Node* getuncle(Node* node);

		void rotate(Node*);
		void shift(Node*);
	public:
		Tree();
		Node* root;

		void insert(int);
		void remove(int);
		void print(Node*, int);
};