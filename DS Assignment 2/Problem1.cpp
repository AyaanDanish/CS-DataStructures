#include <iostream>
using namespace std;

class Node {
public:
    int coeff;
    char var;
    int power;
    bool added;

    Node *next;
    Node(int coeff, char var, int power) {
        this->coeff = coeff;
        this->var = var;
        this->power = power;
        added = false;
        next = NULL;
    }
};

class LinkedList {
public:
    Node *head;

    LinkedList() {
        head = NULL;
    }

    void pushNode(Node *newNode) {
        newNode->next = head;
        head = newNode;
    }

    void addNodeSorted(int coeff, char var, int power) {
        Node *newNode = new Node(coeff, var, power); // Create the new node and pass the value it will hold

        // Special case that is used when list is empty OR list needs insertion at the beginning
        if ((head == NULL) || (newNode->var == head->var && newNode->power < head->power)) {
            pushNode(newNode);
            return;
        }

        Node *ptr = head;
        while ((ptr->next != NULL) && (ptr->next->var != newNode->var) || (ptr->next != NULL) && (ptr->next->power < newNode->power))
            ptr = ptr->next;

        ptr->next = newNode;
    }

    void displayList() {
        if (head == NULL)
            return;

        cout << countNodes() << endl;
        Node *ptr = head;
        while (ptr != NULL) {
            cout << ptr->coeff << " " << ptr->var << " " << ptr->power << endl;
            ptr = ptr->next;
        }
    }

    int countNodes() {
        Node *ptr = head;
        int count = 0;
        while (ptr != NULL) {
            count++;
            ptr = ptr->next;
        }
        return count;
    }
    bool isEmpty() {
        return (head == NULL);
    }

    void addPoly(LinkedList list1, LinkedList list2) {
        if (list1.isEmpty() && list2.isEmpty())
            return;

        if (list1.isEmpty()) {
            Node *ptr = list2.head;
            while (ptr != NULL) {
                this->addNodeSorted(ptr->coeff, ptr->var, ptr->power);
                ptr->added = true;
                ptr = ptr->next;
            }
            return;
        }

        if (list2.isEmpty()) {
            Node *ptr = list1.head;
            while (ptr != NULL) {
                this->addNodeSorted(ptr->coeff, ptr->var, ptr->power);
                ptr->added = true;
                ptr = ptr->next;
            }
            return;
        }

        Node *ptr1 = list1.head;
        Node *ptr2 = list2.head;

        while (ptr1 != NULL) {
            ptr2 = list2.head;
            while (ptr2 != NULL) {
                if (ptr2->var == ptr1->var && ptr2->power == ptr1->power) {
                    this->addNodeSorted(ptr1->coeff + ptr2->coeff, ptr1->var, ptr1->power);
                    ptr2->added = ptr1->added = true;
                    break;
                }
                ptr2 = ptr2->next;
            }
            if (ptr2 == NULL) {
                this->addNodeSorted(ptr1->coeff, ptr1->var, ptr1->power);
                ptr1->added = true;
            }
            ptr1 = ptr1->next;
        }

        ptr2 = list2.head;
        while (ptr2 != NULL) {
            if (!ptr2->added)
                this->addNodeSorted(ptr2->coeff, ptr2->var, ptr2->power);
            ptr2 = ptr2->next;
        }
    }
};

int main() {
    LinkedList list1;
    LinkedList list2;
    LinkedList list3;

    int list1Nodes, list2Nodes;
    int coeff, power;
    char var;
    cin >> list1Nodes;
    for (int i = 0; i < list1Nodes; i++) {
        cin >> coeff >> var >> power;
        list1.addNodeSorted(coeff, var, power);
        fflush(stdin);
    }

    cin >> list2Nodes;
    for (int i = 0; i < list2Nodes; i++) {
        cin >> coeff >> var >> power;
        list2.addNodeSorted(coeff, var, power);
        fflush(stdin);
    }

    list3.addPoly(list1, list2);
    list3.displayList();
    fflush(stdin);
    cin.get();
}
