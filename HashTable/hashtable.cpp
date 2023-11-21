#include<iostream>
#define SIZE 11
#define hash 10001
using namespace std;


struct Node {
	int data;
	Node* next;
};

void initTable(Node* table[]) {
	for (int i = 0; i < SIZE; i++) {
		table[i] = NULL;
	}
}

Node* initNode(int val) {
	Node* tmp = new Node{ val, NULL };
	return tmp;
}

void addFirst(Node*& node, int val) {
	Node* tmp = initNode(val);
	if (node == NULL) {
		node = tmp;
	}
	else {
		tmp->next = node;
		node = tmp;
	}
}

int hashing(int val) {
	return val % SIZE;
}

void insertData(Node* table[], int val) {
	int index = hashing(val);
	Node* tmp = initNode(val);
	addFirst(table[index], val);
}
void input(Node* table[]) {
	int a[] = { 1,4,56,77,67,53,6,7,3,23,35 };
	for (int i = 0; i < SIZE; i++) {
		insertData(table, a[i]);
	}
}
void output(Node* table[]) {
	for (int i = 0; i < SIZE; i++) {
		cout << i << ": ";
		Node* current = table[i];
		while (current != NULL) {
			cout << current->data << "   ";
			current = current->next;
		}
		cout << endl;
	}
}

int findNode(Node* table[], int val) {
	int index = hashing(val);
	Node* current = table[index];
	while (current) {
		if (current->data == val)
			return 1;
		current = current->next;
	}
	return 0;
}

int main() {
	Node* table[SIZE];
	initTable(table);
	input(table);
	output(table);
	int val;
	cout << "Value: "; cin >> val;
	cout << findNode(table, val) << endl;
	return 0;
}