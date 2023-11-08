#include<iostream>
#include<queue>
#include<list>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};

Node* createNode(int x) {
    Node* node = new Node;
    node->data = x;
    node->left = node->right = NULL;
    return node;
}

void insertData(Node*& root, int data) {
    Node* tmp = new Node;
    tmp->data = data;
    tmp->left = tmp->right = NULL;
    if (root == NULL) {
        root = tmp;
    }
    else {
        if (data < root->data) {
            // Duyet qua trai de them phan tu x
            insertData(root->left, data);
        }
        else if (data > root->data) {
            // Duyet qua phai de them phan tu x
            insertData(root->right, data);
        }
    }
}

void NLR(Node* root) {
    if (root != NULL) {
        cout << "  " << root->data;
        NLR(root->left);
        NLR(root->right);
    }
}

void LNR(Node* root) {
    if (root != NULL) {
        NLR(root->left);
        cout << "  " << root->data;
        NLR(root->right);
    }
}

void LRN(Node* root) {
    if (root != NULL) {
        NLR(root->left);
        NLR(root->right);
        cout << "  " << root->data;
    }
}

void LevelOrder(Node* root) {
    queue<Node*> queue;
    queue.push(root);
    while (!queue.empty()) {
        Node* tmp = queue.front();
        cout << "  " << tmp->data;
        if (tmp->left != NULL) {
            queue.push(tmp->left);
        }
        if (tmp->right != NULL) {
            queue.push(tmp->right);
        }
    }
}

void Search(Node* root, int x) {
    if (root == NULL)
        return;
    if (x < root->data)
        Search(root->left, x);
    if (x > root->data)
        Search(root->right, x);
    if (root->data == x)
        cout << root->data;
}

int main() {
    Node* root = NULL;
    int a[] = { 3,-5,-9,-3,0,7,-8,9,-4,10,4,-7,15,-6 };
    for (int i = 0; i < 14; i++) {
        insertData(root, a[i]);
    }
       cout << "\n\nNLR: "; NLR(root);
       cout << "\n\nLNR: "; LNR(root);
       cout << "\n\nLRN: "; LRN(root);
       cout << "\n\nLevelOrder: "; LevelOrder(root);
    int x;
    cout << "x = "; cin >> x;
    //    Search(root, x);
    insertData(root, x);
    cout << endl;
    NLR(root);
    cout << endl;
    //////


    return 0;
}