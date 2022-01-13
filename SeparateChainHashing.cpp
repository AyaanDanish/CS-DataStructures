#include <climits>
#include <iostream>
#include <string.h>
using namespace std;
const int TABLE_SIZE = 17;

class ContactNode {
public:
    int studentID;
    string number;
    ContactNode *next;
    ContactNode(int studentID, string number) {
        this->studentID = studentID;
        this->number = number;
        this->next = NULL;
    }
    ContactNode() {
        this->studentID = -1;
        this->number = "null";
        this->next = NULL;
    }
};

class ContactBook {
    ContactNode *table[TABLE_SIZE];

public:
    ContactBook() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = NULL;
        }
    }

    int divisionHash(int value) {
        return value % TABLE_SIZE;
    }

    void insert(int studentID, string number) {
        ContactNode *newNode = new ContactNode(studentID, number);
        int i = divisionHash(studentID);

        // No clashes occur, there is no LL at the calculated index
        if (table[i] == NULL) {
            table[i] = newNode;
            return;
        }
        // Clash occured, so link new node to the end of the existing LL
        ContactNode *ptr = table[i];
        while (ptr->next != NULL)
            ptr = ptr->next;
        ptr->next = newNode;
    }

    void search(int searchID) {
        int i = divisionHash(searchID);

        // Traverse the LL at the calculated index to search for the given ID
        ContactNode *ptr = table[i];
        while (ptr->studentID != searchID)
            ptr = ptr->next;

        // If it wasn't found, ptr will be NULL
        if (ptr == NULL) {
            cout << "Value not found in Contact Book!";
            return;
        }
        cout << "Value found at index " << i;
    }

    void removeByID(int removeID) {
        int i = divisionHash(removeID);

        ContactNode *back = NULL;
        ContactNode *fwd = table[i];
        // If first node in LL needs to be deleted
        if (fwd->studentID == removeID) {
            table[i] = table[i]->next;
            delete fwd;
            return;
        }

        while (fwd->studentID != removeID) {
            back = fwd;
            fwd = fwd->next;
        }
        // If value not found
        if (fwd == NULL) {
            cout << "Value not found in Contact Book!";
            return;
        }
        back->next = fwd->next;
        delete fwd;
    }

    bool isEmpty() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (table[i] != NULL)
                return false;
        }
        return true;
    }

    int contactCount() {
        int count = 0;
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (table[i] != NULL)
                count++;
        }
        return count;
    }

    void display() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (table[i] == NULL)
                cout << i << " | "
                     << "Empty" << endl;
            else {
                ContactNode *ptr = table[i];
                cout << i << " | ";
                while (ptr != NULL) {
                    cout << "ID: " << ptr->studentID << ", Number: " << ptr->number << " | ";
                    ptr = ptr->next;
                }
                cout << endl;
            }
        }
    }
};

int main() {
    ContactBook book;
    book.insert(17, "+923212687801");
    book.insert(34, "+923212687801");
    book.insert(4, "+923362145486");
    book.insert(99, "+923212238353");
    book.insert(25, "+923243821155");
    book.display();
}