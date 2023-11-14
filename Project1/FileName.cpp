#include<iostream>
#include<queue>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};

////////////////////////////////////////////////
void initTree(Node* tree) {
    tree = NULL;
}
void insertData(Node*& root, int data) {
    Node* tmp = new Node;
    tmp->data = data;
    tmp->left = tmp->right = NULL;
    if (root == NULL)
        root = tmp;
    else
        if (data < root->data) 
            insertData(root->left, data);
        else if (data > root->data)
            insertData(root->right, data);
}

void preOrder(Node* root) {//N-L-R (tien thu tu)
    if (root != NULL) {
        cout << "  " << root->data;
        preOrder(root->left);
        preOrder(root->right);
    }
}
void inOrder(Node* root) {//L-N-R (trung thu tu)
    if (root != NULL) {
        inOrder(root->left);
        cout << "  " << root->data;
        inOrder(root->right);
    }
}
void postOrder(Node* root) {//L-R-N (hau thu tu)
    if (root != NULL) {
        postOrder(root->left); 
        postOrder(root->right);
        cout << "  " << root->data;
    }
}
void levelOrder(Node* root) {// duyet theo muc
    queue<Node*> queue;
    queue.push(root);
    while (!queue.empty()) {
        Node* tmp = queue.front();
        cout << "  " << tmp->data;
        queue.pop();
        if (tmp->left != NULL) {
            queue.push(tmp->left);
        }
        if (tmp->right != NULL) {
            queue.push(tmp->right);
        }
    }
}

void removeLeaf(Node*& leaf) {
    leaf = NULL;
}
void removeOneChild(Node*& node) {
    if (node->left == NULL)
        node = node->right;
    if (node->right == NULL)
        node = node->left;
}
void removeTwoChild(Node*& node) {
    Node* left = node->left;
    while (left->right->right != NULL)
        left = left->right;
    node->data = left->right->data;
    left->right = NULL;
}

void removeNode(Node*& root, int x) {
    if (root == NULL)
        return;
    if (x < root->data) {
        removeNode(root->left, x);
    }
    if (x > root->data) {
        removeNode(root->right, x);
    }
    if (root->data == x) {
        if (root->left == NULL && root->right == NULL) {
            removeLeaf(root);
        }
        else if ((root->left == NULL && root->right != NULL) || (root->left != NULL && root->right == NULL)) {
            removeOneChild(root);
        }
        else if (root->left != NULL && root->right != NULL) {
            removeTwoChild(root);
        }
        return;
    }
}

void removeTree(Node*& tree) {
    tree = NULL;
}

int heightTree(Node* root) {
    if (root == NULL)
        return 0;
    int left = heightTree(root->left);
    int right = heightTree(root->right);
    return max(left, right) + 1;
}

int countNode(Node* root) {
    if (root == NULL)
        return 0;
    return 1 + countNode(root->left) + countNode(root->right);
}

int sumNode(Node* root) {
    if (root == NULL)
        return 0;
    return root->data + sumNode(root->left) + sumNode(root->right);
}

int findHeightNodeX(Node* root, int x) {
    if (x == root->data)
        return 0;
    int height = 1;
    while (root != NULL && root->data != x) {
        if (x < root->data)
            root = root->left;
        if (x > root->data)
            root = root->right;
        height++;
    }
    if (root == NULL)
        return -1;
    return height;
}

int countLeaf(Node* root) {
    if (root == NULL)
        return 0;
    if (root->left == NULL && root->right == NULL)
        return 1;
    else
        return countLeaf(root->left) + countLeaf(root->right);
}

int levelNode(Node* root, Node* p) {
    int level = -1;
    if (root == NULL && p == NULL)
        return level;
    while (root != NULL) {
        if (root->data > p->data) {
            root = root->left;
            level++;
        }
        else {
            root = root->right;
            level++;
        }
    }
    return level;
}

int countLess(Node* root, int x) {
    if (root == NULL)
        return 0;
    if (root->data < x)
        return 1 + countLess(root->left, x) + countLess(root->right, x);
    else
        return countLess(root->left, x) + countLess(root->right, x);
}

int countGreater(Node* root, int x) {
    if (root == NULL)
        return 0;
    if (root->data > x)
        return 1 + countGreater(root->left, x) + countGreater(root->right, x);
    else
        return countGreater(root->left, x) + countGreater(root->right, x);
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

bool isFullBST(Node* root) {
    if (root == NULL)
        return 0;
    int n = heightTree(root);
    if (n == 0 || n == 1)
        return true;
    queue<Node*>queue;
    queue.push(root);
    while (!queue.empty()) {
        Node* tmp = queue.front();
        queue.pop();
        if (tmp->left == NULL || tmp->right == NULL)
            return false;
        queue.push(tmp->left);
        queue.push(tmp->right);
    }
    return true;
}


////////////////////        AVL        //////////////////

void rotateRight(Node*& root) {
    Node* temp = root->left;
    root->left = temp->right;
    temp->right = root;
    root = temp;
}

void rotateLeft(Node*& root) {
    Node* temp = root->right;
    root->right = temp->left;
    temp->left = root;
    root = temp;
}

void AVL(Node*& root) {
    int balance = heightTree(root->left) - heightTree(root->right);
    if (balance > 1) {          // left
        while (abs(balance) > 1) {
            Node* left = root->left;
            int balanceChild = heightTree(left->left) - heightTree(left->right);
            if (balanceChild < 0) {//right
                rotateLeft(root->left);
                rotateRight(root);
            }
            else
                rotateRight(root);
            balance = heightTree(root->left) - heightTree(root->right);
        }
    }
    else if (balance < -1) {    // right
        while (abs(balance) > 1) {
            Node* right = root->right;
            int balanceChild = heightTree(right->left) - heightTree(right->right);
            if (balanceChild > 0) { // left
                rotateRight(root->right);
                rotateLeft(root);
            }
            else
                rotateLeft(root);
            balance = heightTree(root->left) - heightTree(root->right);
        }
    }
    AVL(root->left);
    AVL(root->right);
}

//////////////////////////////////////////


void Menu(Node*& root) {
    int a[] = { 3,-5,-9,-3,0,7,-8,9,-4,10,4,-7,15,-6 ,16,17 };
//  int n; cin >> n;
    for (int i = 0; i < 16; i++) {
        //      int data;
        //      cout << "Data = "; cin >> data;
        //        insertData(root, a[i]);
        insertData(root, a[i]);
    }
    while (1) {       
        cout << "\n=========Menu=========";
        cout << "\n 0. Ket thuc";
        cout << "\n 1. Nhap du lieu";
        cout << "\n 2. Xuat du lieu";
        cout << "\n 3. Xoa du lieu";
        cout << "\n 4. Chieu cao cua cay";
        cout << "\n 5. Dem so luong Node";
        cout << "\n 6. Tong cac Node";
        cout << "\n 7. Chieu cao cua 1 Node cho truoc";
        cout << "\n 8. Can bang cay";
        cout << "\n 9. So nut la";
        cout << "\n10. Tang cua 1 nut";
        cout << "\n11. So nut nho hon x";
        cout << "\n12. So nut lon hon x";
        cout << "\n13. Kiem tra BST";
        cout << "\n14. Cay nhi phan tim kiem day du";
        cout << "\n======================";
        int choose;
        cout << "\n\nChon: "; cin >> choose;  
        switch (choose) {
        case 0: {
            return;
        }
        case 1: {
//            int a[] = { 3,-5,-9,-3,0,7,-8,9,-4,10,4,-7,15,-6 };
//            int n; cin >> n;
//            for (int i = 0; i < 14; i++) {
//                int data;
//                cout << "Data = "; cin >> data;
//                insertData(root, a[i]);
//            }
//            system("pause");
//            system("cls");
//            break;
        }
        case 2: {
            cout << "\nTien thu tu:\n";
            preOrder(root);
       /*     cout << "\nTrung thu tu:\n";
            inOrder(root);
            cout << "\nHau thu tu:\n";
            postOrder(root);
            cout << "\nBFS:\n";
            levelOrder(root);*/
            cout << endl;
            system("pause");
            system("cls");
            break;
        }
        case 3: {
            cout << "\nTien thu tu:\n";
            preOrder(root);
            int x;
            cout << "\n\nGia tri node can xoa: ";
            cin >> x;
            removeNode(root, x);
            cout << "\nTien thu tu:\n";
            preOrder(root);
            cout << endl;
            system("pause");
            system("cls");
            break;
        }
        case 4: {
            cout << "  " << heightTree(root) << endl;
            cout << endl;
            system("pause");
            system("cls");
            break;
        }
        case 5: {
            cout << "So luong Node: " << countNode(root) << endl;
            cout << endl;
            system("pause");
            system("cls");
            break;
        }
        case 6: {
            cout << "Tong ca Node: " << sumNode(root) << endl;
            cout << endl;
            system("pause");
            system("cls");
            break;
        }
        case 7: {
            int x;
            cout << "Node can tim chieu cao: "; cin >> x;
            cout << "Chieu cao cua Node: " << findHeightNodeX(root, x) << endl;
            cout << endl;
            system("pause");
            system("cls");
            break;
        }
        case 8: {
            cout << "\nTien thu tu:\n";
            preOrder(root);
            cout << endl << endl;
            AVL(root);
            cout << "\nTien thu tu:\n";
            preOrder(root);
            cout << endl << endl;
            system("pause");
            system("cls");
            break;
        }
        case 9: {
            cout << "\nSo nut la: " << countLeaf(root) << endl;
            system("pause");
            system("cls");
            break;
        }
        case 10: {
            Node* p = new Node{ -4,NULL,NULL };
            cout << "\nTang cua nut: " << levelNode(root, p) << endl;
            system("pause");
            system("cls");
            break;
        }
        case 11: {
            int x;
            cout << "x = "; cin >> x;
            cout << "\nSo nut nho hon " << x << ": " << countLess(root, x) << endl;
            system("pause");
            system("cls");
            break;
        }
        case 12: {
            int x;
            cout << "x = "; cin >> x;
            cout << "\nSo nut lon hon " << x << ": " << countGreater(root, x) << endl;
            system("pause");
            system("cls");
            break;
        }
        case 13: {
            if (isBST(root))
                cout << "\nLa cay nhi phan tim kiem\n";
            else
                cout << "\nKhong la cay nhi phan tim kiem\n";
            system("pause");
            system("cls");
            break;
        }
        case 14: {
            if (isFullBST(root))
                cout << "\nLa cay nhi phan tim kiem day du\n";
            else
                cout << "\nKhong la cay nhi phan tim kiem day du\n";
            system("pause");
            system("cls");
            break;
        }
        default: {
            system("cls");
            cout << "\nChon khong hop le!!";
            cout << "\nMoi chon lai";
            Menu(root);
        }
        }
    }
}
int main() {
    Node* root = NULL;
    Menu(root);
    return 0;
}



