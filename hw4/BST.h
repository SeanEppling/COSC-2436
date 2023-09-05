#ifndef BST_H
#define BST_H
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct node {
	string val;
	node* left;
	node* right;
};

class bst {
private:
	node* root;

public:
	bst() { root = nullptr; }
	node* getRoot() { return root; }
	void pre(node* cu, ofstream& output) {
		if (cu != nullptr) {
			output << cu->val << endl;
			pre(cu->left, output);
			pre(cu->right, output);
		}
	}
	void in(node* cu, ofstream& output) {
		if (cu != nullptr) {
			in(cu->left, output);
			output << cu->val << endl;
			in(cu->right, output);
		}
	}
	void post(node* cu, ofstream& output) {
		if (cu != nullptr) {
			post(cu->left, output);
			post(cu->right, output);
			output << cu->val << endl;
			//cout << cu->val << endl;
		}
	}
	void insert(string v, node* cu, node* prev) {
		if (cu == nullptr && prev == nullptr) {
			node* temp = new node();
			temp->val = v;
			root = temp;
		}
		else if (cu == nullptr) {
			if (v.length() < prev->val.length()) {
				node* temp = new node();
				temp->val = v;
				prev->left = temp;
			}
			else {
				node* temp = new node();
				temp->val = v;
				prev->right = temp;
			}
		}
		else if (v.length() == cu->val.length()) {
			cu->val = v;
		}
		else {
			if (v.length() < cu->val.length())
				insert(v, cu->left, cu);
			else
				insert(v, cu->right, cu);
		}
	}
	bool empty() { return root == nullptr; }

};

#endif