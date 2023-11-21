#include<iostream>
#include<queue>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    int height;
};

int heightNode(Node* root) {
    if (root == NULL)
        return 0;
    return 1 + max(heightNode(root->left), heightNode(root->right));
}

Node* createNode(int data) {
    Node* tmp = new Node{ data,NULL,NULL ,1 };
    return tmp;
}


void rotateLeft(Node*& root) {
    Node* temp = root->right;
    root->right = temp->left;
    temp->left = root;
    root = temp;
}

void rotateRight(Node*& root) {
    Node* temp = root->left;
    root->left = temp->right;
    temp->right = root;
    root = temp;
}


void insertData(Node*& root, int data) {
    Node* tmp = new Node;
    tmp->data = data;
    tmp->left = tmp->right = NULL;
    if (root == NULL)
        root = tmp;
    else {
        if (data < root->data) {
            // Duyet qua trai de them phan tu x
            insertData(root->left, data);
        }
        else if (data > root->data) {
            // Duyet qua phai de them phan tu x
            insertData(root->right, data);
        }
        else 
            return;
    }
    int balance = heightNode(root->left) - heightNode(root->right);
    if (balance > 1) {          // left
        Node* left = root->left;
        int balanceChild = heightNode(left->left) - heightNode(left->right);
        if (balanceChild < 0) {// left-right
            rotateLeft(root->left);
            rotateRight(root);
        }
        else
            rotateRight(root);
    }
    else if (balance < -1) {    // right
        Node* right = root->right;
        int balanceChild = heightNode(right->left) - heightNode(right->right);
        if (balanceChild > 0) { // left-right
            rotateRight(root->right);
            rotateLeft(root);
        }
        else
            rotateLeft(root);
        balance = heightNode(root->left) - heightNode(root->right);
    }
}
void preOrder(Node* root) {//N-L-R (tien thu tu)
    if (root != NULL) {
        cout << "  " << root->data;/* << "(" << root->height << ")";*/
        preOrder(root->left);
        preOrder(root->right);
    }
}
void levelOrder(Node* root) {
    queue<Node*> queue;
    queue.push(root);
    while (!queue.empty()) {
        Node* tmp = queue.front();
        queue.pop();
        cout << "  " << tmp->data;
        if (tmp->left != NULL) {
            queue.push(tmp->left);
        }
        if (tmp->right != NULL) {
            queue.push(tmp->right);
        }
    }
}

bool isBST(Node* root) {
    if (root == NULL)
        return true;
    if (root->left != NULL)
        if (root->data < root->left->data)
            return false;
    if (root->right != NULL)
        if (root->data > root->right->data)
            return false;
    return isBST(root->left) && isBST(root->right);
}

bool isAVL(Node* root) {
    if (!isBST(root))
        return false;
    queue<Node*>queue;
    queue.push(root);
    while (!queue.empty()) {
        Node* tmp = queue.front();
        queue.pop();
        int balance = heightNode(tmp->left) - heightNode(tmp->right);
        if (abs(balance) > 1)
            return false;
        if (tmp->left != NULL)
            queue.push(tmp->left);
        if (tmp->right != NULL)
            queue.push(tmp->right);
    }
    return true;
}

int main() {
    Node* root = NULL;
    int a[] = { 3,-5,-9,-3,0,7,-8,9,-4,10,4,-7,15,-6 ,16,17 };
    for (int i = 0; i < 16; i++) {
        insertData(root, a[i]);
    }
    cout << endl;
    levelOrder(root);
    if (isAVL(root))
        cout << "\nDung\n\n";
    else
        cout << "\nSai\n\n";
    cout << endl;
    return 0;
}