#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class Node {
public:
    string text;
    Node *next;
    Node *prev;

    Node(string text) {
        this->text = text;
        next = NULL;
        prev = NULL;
    }
};

class DoublyLinkedList {
public:
    Node *head;

    DoublyLinkedList() {
        head = NULL;
    }

    void addNodeToEnd(string text) {
        Node *newNode = new Node(text); //Create the new node and pass the value it will hold

        if (head == NULL) { //If head of current LL is NULL (there's no nodes)
            head = newNode; //Head now points to newly created node
            return;
        }

        //If current LL already had nodes
        Node *ptr = head;         //Create a node pointer to traverse the list
        while (ptr->next != NULL) // Traverse the list to arrive at last node (don't surpass it)
            ptr = ptr->next;

        ptr->next = newNode; //Last node now points to new node
        newNode->prev = ptr; //Prev of new node points to the node before it
    }

    //Simply traverses the list and couts the data part
    void displayList() {
        if (head == NULL) {
            return;
        }
        Node *ptr = head;
        while (ptr != NULL) {
            cout << ptr->text << endl;
            ptr = ptr->next;
        }
    }
};

bool stringsAreEqual(string first, string second) {
    if (first.length() != second.size())
        return false;

    for (int i = 0; i < first.size(); i++)
        if (tolower(first[i]) != tolower(second[i]))
            return false;

    return true;
}

int main() {
    DoublyLinkedList list;
    string input;
    //Input the string of text from user
    getline(cin, input);

    //String vector to hold each individual word
    vector<string> wordVector;

    //Stringstream object of the input text, treats the text as a stream (just like when you cin multiple strings separated by a space)
    stringstream stream(input);

    //Intermediate string var to hold each token
    string token;

    //Loop will tokenize each word using space as delimiter and push it into wordVector, but only if the string has not already been added
    bool repeat = false;
    while (getline(stream, token, ' ')) {
        repeat = false;
        for (int i = 0; i < wordVector.size(); i++) {
            if (stringsAreEqual(token, wordVector[i]))
                repeat = true;
        }
        if (!repeat)
            wordVector.push_back(token);
    }

    for (int i = 0; i < wordVector.size(); i++) {
        for (int j = 0; j < wordVector.size() - i - 1; j++) {
            if (strcasecmp(wordVector[j].c_str(), wordVector[j + 1].c_str()) > 0)
                swap(wordVector[j], wordVector[j + 1]);
        }
    }

    for (int i = 0; i < wordVector.size(); i++)
        list.addNodeToEnd(wordVector[i]);

    list.displayList();
    fflush(stdin);
    cin.get();
}
