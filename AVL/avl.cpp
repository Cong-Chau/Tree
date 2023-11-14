#include<iostream>
#include<queue>
using namespace std;

struct Node {
	int data;
	Node* left;
	Node* right;
};

Node* create_node(int value) {
	Node* newNode = new Node;
	newNode->data = value;
	newNode->right = nullptr;
	newNode->left = nullptr;
	return newNode;
}
int height(Node* root) {
	if (root == nullptr) return 0;
	return 1 + max(height(root->right), height(root->left));
}
void Browser_NRL(Node* root) {
	if (root == nullptr)return;
	cout << root->data << "    ";
	Browser_NRL(root->right);
	Browser_NRL(root->left);
}
void rotate_right(Node*& root) {
	Node* tmp = root->left;
	root->left = tmp->right;
	tmp->right = root;
	root = tmp;
}
void rotate_left(Node*& root) {
	Node* tmp = root->right;
	root->right = tmp->left;
	tmp->left = root;
	root = tmp;
}
void insert(Node*& root, int value) { 
	if (root == nullptr)
		root = create_node(value);
	else if (root->data < value)
		insert(root->right, value);
	else if (root->data > value)
		insert(root->left, value);
	int Valbalance = height(root->left) - height(root->right);
	if (Valbalance > 1 && root->left->data < value) {
		rotate_left(root->left);
		rotate_right(root);
	}
	else if (Valbalance > 1 && root->left->data > value) {//left left
		rotate_right(root);
	}
	else if (Valbalance < -1 && root->right->data < value) {//right right
		rotate_left(root);
	}
	else if (Valbalance<-1 && root->right->data > value) {//right left
		rotate_right(root->right);
		rotate_left(root);
	}
}
void delete_node_one_children(Node*& root) {
	//khong con
	if (root->right == nullptr && root->left == nullptr) {
		root = nullptr;
		return;
	}
	//node co 1 con  phai
	Node* tmp = root;
	if (root->left == nullptr && root->right != nullptr) {
		root = root->right;
		delete tmp;
		return;
	}
	//node co 1 con trai
	if (root->left != nullptr && root->right == nullptr) {
		root = root->left;
		delete tmp;
		return;
	}
}
int childre_max_left(Node*& root) {
	if (root->right == nullptr) {
		Node* tmp = root;
		root = root->left;
		int x = tmp->data;
		delete tmp; 
		return x;
	}
	return childre_max_left(root->right);
}
void delete_node_two_children(Node*& root) {
	int temp = childre_max_left(root->left);
	root->data = temp;
}
int valueBlance(Node* root) {
	return height(root->left) - height(root->right);
}
//xoa node 
void delete_node(Node*& root, int value) {
	if (root == NULL)
		return;
	if (root->data == value) {
		if (root->left != nullptr and root->right != nullptr) {
			delete_node_two_children(root);
			delete_node(root->left, root->data);
		}
		else {
			delete_node_one_children(root);
			return;
		}
	}
	else if (root->data > value) {
		delete_node(root->left, value);
	}
	else if (root->data < value)
		delete_node(root->right, value);
	//2.tinh do lech
	int Valbalance = valueBlance(root);
	//3.quay
	//left right
	if (Valbalance > 1 && valueBlance(root->left) < 0) {
		rotate_left(root->left);
		rotate_right(root);
	}
	else if (Valbalance > 1 && valueBlance(root->left) >= 0) {//left left
		rotate_right(root);
	}
	else if (Valbalance < -1 && valueBlance(root->right) <= 0) {//right right
		rotate_left(root);
	}
	else if (Valbalance < -1 && valueBlance(root->right)>0) {//right left
		rotate_right(root->right);
		rotate_left(root);
	}
}