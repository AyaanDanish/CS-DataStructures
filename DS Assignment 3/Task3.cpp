#include <climits>
#include <iostream>
#include <queue>
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

    void traverseLevelOrder(Node *root) {
        if (root == NULL)
            return;

        queue<Node *> q;
        q.push(root); // Push the root

        q.push(NULL); // Push a NULL separator that signifies the end of the current level (Queue: root -> NULL)
        int max = INT_MIN;
        int min = INT_MAX;

        while (!q.empty()) {
            // Pop the front and display it if it isn't NULL
            Node *frontNode = q.front();
            q.pop();

            if (frontNode == NULL) { // If we've reached the end of the current level, NULL will be popped
                cout << min << " " << max << endl;

                if (q.empty())
                    break; // If we popped the last NULL separator in the queue, then break

                // Reset max and min as we are starting a new level
                max = INT_MIN;
                min = INT_MAX;
                q.push(NULL); // Push a NULL separator at the end of whatever is in the queue

                continue; // Continue with next numerical value at the front
            }

            // Update max and min values
            if (frontNode->data > max)
                max = frontNode->data;
            if (frontNode->data < min)
                min = frontNode->data;

            // Enqueue left and right children of front node
            if (frontNode->left != NULL)
                q.push(frontNode->left);
            if (frontNode->right != NULL)
                q.push(frontNode->right);
        }
    }
};

int main() {
    BST tree;
    int n;
    cin >> n;
    int num;
    for (int i = 0; i < n; i++) {
        cin >> num;
        tree.addNode(num);
    }
    tree.traverseLevelOrder(tree.root);
}