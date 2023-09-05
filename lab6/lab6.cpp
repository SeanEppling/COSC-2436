#include <iostream>
#include <fstream>
#include <algorithm>
#include "ArgumentManager.h"
using namespace std;

int max(int a, int b) {
	if (a > b)
		return a;
	else
		return b;
}

struct node {
	int data;
	node* left;
	node* right;
	int height;
	node(int d) {
		data = d;
		left = nullptr;
		right = nullptr;
		height = 0;
	}
};

class avlTree {
private:
	node* root;

public:
	avlTree() { root = nullptr; }

	void add(int data) { root = insert(root, data); }

	node* getRoot() { return root; }

	int findMax(node* cu) {
		if (cu->right == nullptr)
			return cu->data;
		return findMax(cu->right);
	}

	node* insert(node* t, int x) {
		if (t == nullptr)
			t = new node(x);
		else if (x < t->data) {
			t->left = insert(t->left, x);
			if (bFactor(t) == 2) {
				if (x < t->left->data)
					t = singleRight(t);
				else
					t = leftRight(t);
			}
		}
		else if (x > t->data) {
			t->right = insert(t->right, x);
			if (bFactor(t) == -2) {
				if (x > t->right->data)
					t = singleLeft(t);
				else
					t = rightLeft(t);
			}
		}
		t->height = max(height(t->left), height(t->right)) + 1;
		return t;
	}

	node* singleRight(node* t) {
		node* u = t->left;
		t->left = u->right;
		u->right = t;
		t->height = max(height(t->left), height(t->right)) + 1;
		u->height = max(height(u->left), height(u->right)) + 1;
		return u;
	}

	node* singleLeft(node* t) {
		node* u = t->right;
		t->right = u->left;
		u->left = t;
		t->height = max(height(t->left), height(t->right)) + 1;
		u->height = max(height(u->left), height(u->right)) + 1;
		return u;
	}

	node* leftRight(node* t) {
		t->left = singleLeft(t->left);
		return singleRight(t);
	}

	node* rightLeft(node* t) {
		t->right = singleRight(t->right);
		return singleLeft(t);
	}

	int height(node* cu) {
		if (cu == nullptr)
			return -1;
		else
			return cu->height;
	}

	int bFactor(node* cu) {
		return (height(cu->left) - height(cu->right));
	}

	void printLevelOrder(node* cu, ofstream& output)
	{
		int h = height(cu);
		int i;
		for (i = 0; i <= h; i++)
			printCurrentLevel(cu, i, output);
	}

	void printCurrentLevel(node* cu, int level, ofstream& output)
	{
		if (cu == NULL)
			return;
		if (level == 0) {
			
			if (cu->data == findMax(root)) {
				output << cu->data;
				cout << cu->data;
			}
			else {
				output << cu->data << " ";
				cout << cu->data << " ";
			}
		}
		else if (level > 0) {
			printCurrentLevel(cu->left, level - 1, output);
			printCurrentLevel(cu->right, level - 1, output);
		}
	}
};

int main(int argc, char* argv[]) {

	ArgumentManager am(argc, argv);
	ifstream input(am.get("input"));
	ofstream output(am.get("output"));

	//ifstream input("input1.txt");
	//ofstream output("output1.txt");

	avlTree avl;
	int size;
	input >> size;
	for (int i = 0; i < size; i++) {
		int num;
		input >> num;
		cout << num << endl;
		avl.add(num);
	}

	avl.printLevelOrder(avl.getRoot(), output);

	return 0;
}