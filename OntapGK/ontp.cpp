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
    if (root == nullptr)
        return -1;
    else
        return max(heightNode(root->left), heightNode(root->right)) + 1;
}

Node* createNode(int val) {
    Node* tmp = new Node{ val,nullptr,nullptr,1 };
    return tmp;
}

void rotateLeft(Node*& node) {
    Node* tmp = node->right;
    node->right = tmp->left;
    tmp->left = node;
    node = tmp;
    node->height = heightNode(node);
    node->left->height = heightNode(node->left);
}

void rotateRight(Node*& node) {
    Node* tmp = node->left;
    node->left = tmp->right;
    tmp->right = node;
    node = tmp;
    node->height = heightNode(node);
    node->right->height = heightNode(node->right);
}

void insertData(Node*& root, int val) {
    Node* tmp = createNode(val);
    if (root == NULL)
        root = tmp;
    else {
        if (val < root->data)
            insertData(root->left, val);
        else if (val > root->data)
            insertData(root->right, val);
    }

    root->height = heightNode(root);
    int balance = heightNode(root->left) - heightNode(root->right);
    if (balance > 1) {
        Node* left = root->left;
        int balanceLeft = heightNode(left->left) - heightNode(left->right);
        if (balanceLeft >= 0) // L-L
            rotateRight(root);
        else { // L-R
            rotateLeft(root->left);
            rotateRight(root);
        }
    }
    if (balance < -1) {
        Node* right = root->right;
        int balanceRight = heightNode(right->left) - heightNode(right->right);
        if (balanceRight <= 0)// R-R
            rotateLeft(root);

        else { // R-L
            rotateRight(root->left);
            rotateLeft(root);
        }
    }
}

Node* minofRight(Node* root) {
    Node* min = root;
    while (min->left != NULL) {
        min = min->left;
    }
    return min;
}

void removeData(Node*& root, int val) {
    if (root == NULL)
        return;
    if (val < root->data)
        removeData(root->left, val);
    else if (val > root->data)
        removeData(root->right, val);
    else {
        if (root->left == NULL && root->right == NULL) {
            root = NULL;
        }
        else if (root->left == NULL || root->right == NULL) {
            if (root->left != NULL)
                root = root->left;
            if (root->right != NULL)
                root = root->right;
        }
        // tim node nho nhat cua cay con phai
        else if (root->left != NULL && root->right != NULL) {  
            Node* min = minofRight(root);
            root->data = min->data;
            delete(min);
        }
    }
    if (root == nullptr)
        return;
    root->height = heightNode(root);
    int balance = heightNode(root->left) - heightNode(root->right);
    if (balance > 1) {
        Node* left = root->left;
        int balanceLeft = heightNode(left->left) - heightNode(left->right);
        if (balanceLeft >= 0) // L-L
            rotateRight(root);
        else { // L-R
            rotateLeft(root->left);
            rotateRight(root);
        }
    }
    if (balance < -1) {
        Node* right = root->right;
        int balanceRight = heightNode(right->left) - heightNode(right->right);
        if (balanceRight <= 0)// R-R
            rotateLeft(root);

        else { // R-L
            rotateRight(root->left);
            rotateLeft(root);
        }
    }
}

void levelOrder(Node* root) {
    queue<Node*>tmp;
    tmp.push(root);
    while (!tmp.empty()) {
        Node* node = tmp.front();
        tmp.pop();
        cout << "    " << node->data << "(" << node->height << ")";
        if (node->left != nullptr)
            tmp.push(node->left);
        if (node->right != nullptr)
            tmp.push(node->right);
    }
}


int main() {
    Node* root = NULL;
    int a[] = { 5,6,3,-3,-6,-5,7,20,4,13,9,-9,-12 };
    int n = sizeof(a) / sizeof(a[0]);
    for (int i = 0; i < n; i++) {
        insertData(root, a[i]);
    }
    levelOrder(root);
    cout << endl;
    removeData(root, 6);
    cout << endl;
    levelOrder(root);
    cout << endl;
    return 0;
}