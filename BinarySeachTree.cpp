#include <iostream>
#include <vector>
using namespace std;

class Node {
public:
    int data;
    Node *left;
    Node *right;

    Node(int data) {
        this->data = data;
        left = NULL;
        right = NULL;
    }
};

class BST {
public:
    Node *root;

    BST() {
        root = NULL;
    }

    void searchTree(int value) {
        Node *ptr = root;
        while (ptr->data != value && ptr->left != NULL & ptr->right != NULL) {
            if (value < ptr->data)
                ptr = ptr->left;
            if (value > ptr->data)
                ptr = ptr->right;
        }

        if (ptr->data == value)
            cout << "Value found!";
        else
            cout << "Value not found!";
    }

    void addNode(int data) {
        Node *newNode = new Node(data);
        if (root == NULL) {
            root = newNode;
            return;
        }
        Node *ptr = root;
        Node *parent;
        while (ptr != NULL) {
            parent = ptr;
            if (newNode->data > parent->data)
                ptr = ptr->right;
            else
                ptr = ptr->left;
        }
        if (newNode->data > parent->data)
            parent->right = newNode;
        else
            parent->left = newNode;
    }

    void displayInOrder(Node *root) {
        if (root == NULL)
            return;
        displayInOrder(root->left);
        cout << root->data << " ";
        displayInOrder(root->right);
    }
    void displayInOrderLeft(Node *root) {
        if (root == NULL)
            return;
        displayInOrderLeft(root->left);
        cout << root->data << " ";
    }
    void displayInOrderRight(Node *root) {
        if (root == NULL)
            return;
        cout << root->data << " ";
        displayInOrder(root->right);
    }

    void sumOfPaths(Node *root, int sum) {
        if (root == NULL)
            return;
        if (root->left == NULL && root->right == NULL)
            cout << sum + root->data << " ";
        sumOfPaths(root->left, sum + root->data);

        sumOfPaths(root->right, sum + root->data);
    }

    void topDown(Node *root) {
        if (root == NULL)
            return;

        displayInOrderLeft(root);
        displayInOrderRight(root);
    }

    void displayPreOrder(Node *root) {
        if (root == NULL)
            return;
        cout << root->data << " ";
        displayInOrder(root->left);
        displayInOrder(root->right);
    }

    void displayPostOrder(Node *root) {
        if (root == NULL)
            return;
        displayInOrder(root->left);
        displayInOrder(root->right);
        cout << root->data << " ";
    }

    void getMinNode(Node *minRoot, Node *&succ, Node *&parent) {
        Node *ptr = minRoot;
        while (ptr->left != NULL || ptr->right != NULL) {
            parent = ptr;
            ptr = ptr->left;
        }
        succ = ptr;
    }

    void deleteNode(int num) {
        if (root == NULL)
            return;
        Node *ptr = root;
        Node *parent = NULL;
        while (ptr->data != num && ptr->left != NULL && ptr->right != NULL) {
            parent = ptr;
            if (num < ptr->data)
                ptr = ptr->left;
            if (num > ptr->data)
                ptr = ptr->right;
        }
        // Ptr now points to node to be deleted, and parent points to it's parent
        if (ptr == NULL) {
            cout << "Not not found!";
            return;
        }

        // No children case
        if (ptr->left == NULL && ptr->right == NULL) {
            // Make its parent point to NULL first, then delete
            if (ptr == parent->left)
                parent->left = NULL;
            if (ptr == parent->right)
                parent->right = NULL;
            delete ptr;
            return;
        }

        // Only right child case
        if (ptr->left == NULL && ptr->right != NULL) {
            ptr->data = ptr->right->data;
            delete ptr->right;
            ptr->right = NULL;
            return;
        }
        // Only left child case
        if (ptr->right == NULL && ptr->left != NULL) {
            ptr->data = ptr->left->data;
            delete ptr->left;
            ptr->left = NULL;
            return;
        }

        // Both children case
        Node *succ = NULL, *succParent = NULL; // Succ points to inorder successor of node to delete, and succParent points to its parent
        getMinNode(ptr->right, succ, succParent);
        ptr->data = succ->data;
        succParent->left = NULL;
        delete succ;
    }
};

int main() {
    BST tree;
    vector<int> arr = {50, 30, 70, 20, 40, 60, 80};
    for (int i = 0; i < arr.size(); i++)
        tree.addNode(arr[i]);

        tree.topDown(tree.root);
}