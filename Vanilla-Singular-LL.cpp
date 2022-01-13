#include <conio.h>
#include <iostream>
#include <vector>
using namespace std;

class Node {
public:
    int data;
    Node *next;

    Node() {
        data = 0;
        next = NULL;
    }

    Node(int data) {
        this->data = data;
        next = NULL;
    }
};

class LinkedList {
public:
    Node *head;

    LinkedList() {
        head = NULL;
    }

    void addNodeToEnd(int value) {
        Node *newNode = new Node(value); //Create the new node and pass the value it will hold

        if (head == NULL)   //If head of current LL is NULL (there's no nodes)
            head = newNode; //Head now points to newly created node

        else {                        //If current LL already had nodes
            Node *ptr = head;         //Create a node pointer to traverse the list
            while (ptr->next != NULL) // Traverse the list to arrive at last node (don't surpass it)
                ptr = ptr->next;
            ptr->next = newNode; //Last node now points to new node
        }
    }

    //Simply traverses the list and couts the data part
    void displayList() {
        if (head == NULL) {
            cout << "Linked list is currently empty.";
            return;
        }
        cout << "Current linked list: ";
        Node *ptr = head;
        while (ptr != NULL) {
            cout << ptr->data << " ";
            ptr = ptr->next;
        }
    }

    int countNodes() {
        int count = 0;
        Node *ptr = head;
        while (ptr != NULL) {
            count++;
            ptr = ptr->next;
        }
        return count;
    }

    void pushNode(int value) {
        Node *newNode = new Node(value); //Create new node
        newNode->next = head;            //Next part of new node now points to previous head (previously first node)
        head = newNode;                  //Head now points to the new node inserted at the start
    }

    //Function takes in value to be stored at node, and location in LL to attach node to (2 means new node will be 2nd)
    void insertNodeAt(int value, int location) {
        //If the user wanted to add a new node at location 1 (the start), let the pushNode func handle it instead
        if (location == 1) {
            pushNode(value);
            return;
        }
        //If the user wanted to add a new node at the end of the LL, let the addNodeToEnd func handle it
        if (location == countNodes() + 1) {
            addNodeToEnd(value);
            return;
        }

        //Everything in between, this func will handle
        Node *newNode = new Node(value); //Create new node and store the value
        Node *ptr = head;                //Pointer to traverse the list
        int index = 1;                   //Variable to count which list index we are at when traversing

        while (index != location - 1) { //Traverse the list until you arrive at the node before the given location
            ptr = ptr->next;
            index++;
        }

        newNode->next = ptr->next; //First set new node to point to next node in the LL (attach from the right)
        ptr->next = newNode;       //Then set the next of the current node to point to the new one (attach from the left)
    }

    //Function takes in the node number to delete (2 means delete 2nd node)
    void deleteNode(int location) {
        if (location < 1 || location > countNodes()) {
            cout << "\nInvalid location, press any key to try again.";
            cin.get();
            return;
        }

        Node *ptr = head;  //Pointer to traverse the list (points to current node in traversal)
        Node *prev = head; //Pointer to traverse the list (points to node before current)
        int index = 1;

        //If deleting first node, handle that specially
        if (location == 1) {
            head = head->next;
            delete ptr;
            return;
        }

        //Traverse the list until ptr arrives at location to delete. Prev will always point to the node behind ptr.
        while (index != location) {
            prev = ptr;
            ptr = ptr->next;
            index++;
        }

        //Next of previous will point to next of current, disconnecting current node from the list
        prev->next = ptr->next;
        //Then current node is deleted
        delete ptr;
    }

    void updateNode(int value, int location) {
        Node *ptr = head; //Pointer to traverse the list
        int index = 1;

        while (index != location) { //Traverse the list to arrive at node to update
            ptr = ptr->next;
            index++;
        }
        ptr->data = value; //Update the data at the node
    }

    void arrangeOddEven() {
        Node *ptr = head; //Pointer to traverse the list
        vector<int> even; //Vector to hold all even elements in same order as they appear in the LL
        vector<int> odd;  //Similar vector for all odd elements
        //Traverses the list from start to end, saving all even elements in the even vector and all odd elements in the odd vector
        while (ptr != NULL) {
            if (ptr->data % 2 == 0)
                even.push_back(ptr->data);
            else
                odd.push_back(ptr->data);
            ptr = ptr->next;
        }
        ptr = head; //Resets the LL pointer to the start of the LL

        //Traverses the list and sets each LL element to the element from the even vector, until even vector ends
        for (int i = 0; i < even.size(); i++) {
            ptr->data = even[i];
            ptr = ptr->next;
        }
        //Continues traversing the list from where the previous loop left off and repeats the process for the odd vector
        for (int i = 0; i < odd.size(); i++) {
            ptr->data = odd[i];
            ptr = ptr->next;
        }
    }

    void sortList() {
        Node *back = head;
        Node *fwd = head->next;
        int temp;
        while (fwd != NULL) {
            if (fwd->data < back->data) {
                temp = back->data;
                back->data = fwd->data;
                fwd->data = temp;
            }
            fwd = fwd->next;
            back = back->next;
        }
    }
};

int main() {
    LinkedList list;
    int value, location;
    char choice;
    do {
        fflush(stdin);
        system("cls");
        list.displayList();
        cout
            << "\n\n1. Insert a new node at the end" << endl
            << "2. Insert a new node at the start" << endl
            << "3. Insert a new node at any location" << endl
            << "4. Update a node" << endl
            << "5. Delete a node" << endl
            << "6. Arrange the linked list (Task 7)" << endl
            << "7. Sort the list" << endl
            << "0. Exit the program" << endl
            << "\nEnter your choice: ";

        choice = getche();
        fflush(stdin);

        switch (choice) {
        case '1':
            cout << "\nEnter value to store in the new node: ";
            cin >> value;
            list.addNodeToEnd(value);
            break;

        case '2':
            cout << "\nEnter value to store in the new node: ";
            cin >> value;
            list.pushNode(value);
            break;
        case '3':
            cout << "\nEnter value to store in the new node and location in list to insert the node in: ";
            cin >> value >> location;
            list.insertNodeAt(value, location);
            break;

        case '4':
            if (list.head == NULL) {
                cout << "\nThere are no nodes to update, genius. Press enter to return to menu...";
                cin.get();
                break;
            }
            cout << "\nEnter new value for the node and location of node to update: ";
            cin >> value >> location;
            list.updateNode(value, location);
            break;

        case '5':
            if (list.head == NULL) {
                cout << "\nThere are no nodes to delete, genius. Press enter to return to menu...";
                cin.get();
                break;
            }
            cout << "\nEnter location of node to delete: ";
            cin >> location;
            list.deleteNode(location);
            break;

        case '6':
            list.arrangeOddEven();
            break;

        case '7':
            list.sortList();
            break;

        case '0':
            break;

        default:
            cout << "\nInvalid Entry, press any key to try again...";
            cin.get();
            break;
        }
    } while (choice != '0');

}
