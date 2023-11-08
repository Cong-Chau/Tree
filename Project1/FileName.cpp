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

int heightNode(Node* root, int x) {
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

void Menu(Node*& root) {
    int a[] = { 3,-5,-9,-3,0,7,-8,9,-4,10,4,-7,15,-6 };
    //            int n; cin >> n;
    for (int i = 0; i < 14; i++) {
        //                int data;
        //                cout << "Data = "; cin >> data;
        insertData(root, a[i]);
    }
    while (1) {       
        cout << "\n=========Menu=========";
        cout << "\n0. Ket thuc";
        cout << "\n1. Nhap du lieu";
        cout << "\n2. Xuat du lieu";
        cout << "\n3. Xoa du lieu";
        cout << "\n4. Chieu cao cua cay";
        cout << "\n5. Dem so luong Node";
        cout << "\n6. Tong cac Node";
        cout << "\n7. Chieu cao cua 1 Node cho truoc";
        cout << "\n======================";
        int choose;
        cout << "\n\nChon: "; cin >> choose;  
        switch (choose) {
        case 0: {
            return;
        }
        case 1: {
//            int a[] = { 3,-5,-9,-3,0,7,-8,9,-4,10,4,-7,15,-6 };
////            int n; cin >> n;
//            for (int i = 0; i < 14; i++) {
////                int data;
////                cout << "Data = "; cin >> data;
//                insertData(root, a[i]);
//            }
//            system("pause");
//            system("cls");
//            break;
        }
        case 2: {
            cout << "\nTien thu tu:\n";
            preOrder(root);
            cout << "\nTrung thu tu:\n";
            inOrder(root);
            cout << "\nHau thu tu:\n";
            postOrder(root);
            cout << "\nBFS:\n";
            levelOrder(root);
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
            cout << "Chieu cao cua Node: " << heightNode(root, x) << endl;
            cout << endl;
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



