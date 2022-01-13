#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
int n;
class LLNode {
public:
    string data;
    LLNode *next;

    LLNode() {
        data = "";
        next = NULL;
    }

    LLNode(string data) {
        this->data = data;
        next = NULL;
    }
};

class BSTNode {
public:
    string data;
    int numWords;
    BSTNode *left;
    BSTNode *right;

    BSTNode(string data, int numWords) {
        this->data = data;
        this->numWords = numWords;
        left = NULL;
        right = NULL;
    }
};

class LinkedList {
public:
    LLNode *head;

    LinkedList() {
        head = NULL;
    }

    void searchList(BSTNode *bstNode) {
        LLNode *ptr = head;

        // We must separate out each word stored in the BSTNode for comparison, as the LL holds one word per node
        stringstream stream(bstNode->data);
        vector<string> nodeWords;
        string token;
        while (getline(stream, token, ' '))
            nodeWords.push_back(token); // nodeWords contains each individual words of the node

        int matchCount; // Keeps track of how many words have matched
        while (ptr != NULL) {
            matchCount = 0;
            if (ptr->data == nodeWords[0]) {                 // If first word matched, then compare all the next words
                matchCount++;                                // Increment count as first word has matched
                LLNode *matchPtr = ptr->next;                // Use a new pointer to traverse from here and match the next words
                for (int i = 1; i < nodeWords.size(); i++) { // Starts comparing from 1st index as 0th index already matched
                    if (matchPtr->data == nodeWords[i])
                        matchCount++;
                    matchPtr = matchPtr->next;
                }
                if (matchCount == bstNode->numWords) { // If we matched all words, print head node and return
                    cout << head->data << " ";
                    return;
                }
            }
            ptr = ptr->next; // Otherwise, keep trying
        }
    }

    void addNodeToEnd(string value) {
        LLNode *newNode = new LLNode(value);

        if (head == NULL)
            head = newNode;

        else {
            LLNode *ptr = head;
            while (ptr->next != NULL)
                ptr = ptr->next;
            ptr->next = newNode;
        }
    }
};

LinkedList **lists = new LinkedList *[n];

class BST {
public:
    BSTNode *root;

    BST() {
        root = NULL;
    }

    void addNode(string data, int spaces) {
        BSTNode *newNode = new BSTNode(data, spaces);
        if (root == NULL) {
            root = newNode;
            return;
        }
        BSTNode *ptr = root;
        BSTNode *parent;
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

    void traverseInOrder(BSTNode *root) {
        if (root == NULL)
            return;
        traverseInOrder(root->left);

        cout << root->data << " ";

        for (int i = 0; i < n; i++)
            lists[i]->searchList(root);
        cout << endl;

        traverseInOrder(root->right);
    }
};

int main() {

    BST tree;
    int numOfTerms;
    cin >> numOfTerms;

    for (int i = 0; i < numOfTerms; i++) {
        int spaces = 0;
        string term;
        getline(cin, term);
        fflush(stdin);

        for (int i = 0; i < term.length(); i++) { // Counts number of spaces in the string
            if (term[i] == ' ')
                spaces++;
        }
        tree.addNode(term, spaces + 1); // Num of numWords = num of spaces + 1
    }

    cin >> n;
    fflush(stdin);
    for (int i = 0; i < n; i++)
        lists[i] = new LinkedList;

    for (int i = 0; i < n; i++) {
        vector<string> tokenVector;
        bool repeat = false;
        string line, token;
        getline(cin, line);
        fflush(stdin);
        stringstream stream(line);
        while (getline(stream, token, ' ')) {
            repeat = false;
            for (int i = 0; i < tokenVector.size(); i++) {
                if (token == tokenVector[i])
                    repeat = true;
            }
            if (!repeat)
                tokenVector.push_back(token);
        }

        for (int j = 0; j < tokenVector.size(); j++)
            lists[i]->addNodeToEnd(tokenVector[j]);
    }

    tree.traverseInOrder(tree.root);
}
