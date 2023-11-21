#include <iostream>
#include <algorithm>
#include<queue>

struct NODE {
    int data;
    int height;
    NODE* left;
    NODE* right;

    NODE(int val) : data(val), height(1), left(nullptr), right(nullptr) {}
};


NODE* createNode(int data) {
    return new NODE(data);
}


int updateHeight(NODE* node) {
    if (node == nullptr)
        return -1;
    int leftHeight = (node->left) ? node->left->height : 0;
    int rightHeight = (node->right) ? node->right->height : 0;
    return 1 + std::max(leftHeight, rightHeight);
}


int balanceFactor(NODE* node) {
    if (node == nullptr)
        return 0;
    int leftHeight = (node->left) ? node->left->height : 0;
    int rightHeight = (node->right) ? node->right->height : 0;
    return leftHeight - rightHeight;
}


NODE* rotateRight(NODE* y) {
    NODE* x = y->left;
    NODE* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = updateHeight(y);
    x->height = updateHeight(x);

    return x;
}


NODE* rotateLeft(NODE* x) {
    NODE* y = x->right;
    NODE* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = updateHeight(x);
    y->height = updateHeight(y);

    return y;
}


void insert(NODE*& pRoot, int x) {
    if (pRoot == nullptr) {
        pRoot = createNode(x);
        return;
    }

    if (x < pRoot->data)
        insert(pRoot->left, x);
    else if (x > pRoot->data)
        insert(pRoot->right, x);


    pRoot->height = updateHeight(pRoot);

    int balance = balanceFactor(pRoot);

    if (balance > 1 && x < pRoot->left->data)
        pRoot = rotateRight(pRoot);
    else if (balance < -1 && x > pRoot->right->data)
        pRoot = rotateLeft(pRoot);
    else if (balance > 1 && x > pRoot->left->data) {
        pRoot->left = rotateLeft(pRoot->left);
        pRoot = rotateRight(pRoot);
    }
    else if (balance < -1 && x < pRoot->right->data) {
        pRoot->right = rotateRight(pRoot->right);
        pRoot = rotateLeft(pRoot);
    }
}

NODE* findMin(NODE* node) {
    while (node->left != nullptr)
        node = node->left;
    return node;
}

void remove(NODE*& pRoot, int x) {
    if (pRoot == nullptr)
        return;

    if (x < pRoot->data)
        remove(pRoot->left, x);
    else if (x > pRoot->data)
        remove(pRoot->right, x);
    else {
        if (pRoot->left == nullptr || pRoot->right == nullptr) {
            NODE* temp = pRoot->left ? pRoot->left : pRoot->right;
            if (temp == nullptr) {
                temp = pRoot;
                pRoot = nullptr;
            }
            else
                *pRoot = *temp;
            delete temp;
        }
        else {
            NODE* temp = findMin(pRoot->right);
            pRoot->data = temp->data;
            remove(pRoot->right, temp->data);
        }
    }

    if (pRoot == nullptr)
        return;

    pRoot->height = updateHeight(pRoot);

    int balance = balanceFactor(pRoot);

    if (balance > 1 && balanceFactor(pRoot->left) >= 0)
        pRoot = rotateRight(pRoot);
    else if (balance > 1 && balanceFactor(pRoot->left) < 0) {
        pRoot->left = rotateLeft(pRoot->left);
        pRoot = rotateRight(pRoot);
    }
    else if (balance < -1 && balanceFactor(pRoot->right) <= 0)
        pRoot = rotateLeft(pRoot);
    else if (balance < -1 && balanceFactor(pRoot->right) > 0) {
        pRoot->right = rotateRight(pRoot->right);
        pRoot = rotateLeft(pRoot);
    }
}

void NLR(NODE* pRoot) {
    if (pRoot == nullptr)
        return;

    std::cout << "Key: " << pRoot->data << ", Height: " << pRoot->height << std::endl;
    NLR(pRoot->left);
    NLR(pRoot->right);
}

void LNR(NODE* pRoot) {
    if (pRoot == nullptr)
        return;

    LNR(pRoot->left);
    std::cout << "Key: " << pRoot->data << ", Height: " << pRoot->height << std::endl;
    LNR(pRoot->right);
}

void LRN(NODE* pRoot) {
    if (pRoot == nullptr)
        return;

    LRN(pRoot->left);
    LRN(pRoot->right);
    std::cout << "Key: " << pRoot->data << ", Height: " << pRoot->height << std::endl;
}


void levelOrder(NODE* pRoot) {
    if (pRoot == nullptr)
        return;

    std::queue<NODE*> q;
    q.push(pRoot);

    while (!q.empty()) {
        NODE* current = q.front();
        q.pop();

        std::cout << "Key: " << current->data << ", Height: " << current->height << std::endl;

        if (current->left != nullptr)
            q.push(current->left);
        if (current->right != nullptr)
            q.push(current->right);
    }
}


bool isAVL(NODE* pRoot) {
    if (pRoot == nullptr)
        return true;

    int balance = balanceFactor(pRoot);

    return std::abs(balance) <= 1 && isAVL(pRoot->left) && isAVL(pRoot->right);
}

int main() {
    NODE* root = nullptr;

    int a[] = { 5,6,3,-3,-6,-5,7,20,4,13,9,-9,-12 };
    int n = sizeof(a) / sizeof(a[0]);
    for (int i = 0; i < n; i++) {
        insert(root, a[i]);
    }



    std::cout << "\nDuyet theo tang:" << std::endl;
    levelOrder(root);

   



    return 0;
}
