#include <iostream>
#include <vector>
using namespace std;

class Node {
public:
    string ID;
    int totalTime;
    int quota;
    Node *next;

    Node(string ID, int totalTime, int quota) {
        this->ID = ID;
        this->totalTime = totalTime;
        this->quota = quota;
        next = NULL;
    }
};

class CircularLinkedList {
public:
    Node *head;

    CircularLinkedList() {
        head = NULL;
    }

    void addNodeToEnd(string ID, int totalTime, int quota) {
        Node *newNode = new Node(ID, totalTime, quota); //Create the new node and pass the value it will hold

        if (head == NULL) {
            head = newNode;
            newNode->next = head;
            return;
        }

        //If current LL already had nodes
        Node *ptr = head;         //Create a node pointer to traverse the list
        while (ptr->next != head) // Traverse the list to arrive at last node (don't surpass it)
            ptr = ptr->next;
        ptr->next = newNode; //Last node now points to new node
        newNode->next = head;
    }

    //Function accepts number of processes in the queue
    void runProcesses(int numProcesses) {
        if (head == NULL) {
            cout << "There are no processes queued!";
            return;
        }
        //Complete var keeps track of how many processes have been completed.
        //When all processes are done, loop ends.
        int complete = 0;
        Node *ptr = head;
        //Keep going until all processes are complete
        while (complete != numProcesses) {
            //If the current process is complete then do nothing and move to next process
            if (ptr->totalTime == 0) {
                ptr = ptr->next;
                continue;
            }
            //If not complete, print the process ID and decrement total time for process
            cout << ptr->ID << endl;
            ptr->totalTime -= ptr->quota;
            //If decrementing totalTime completed the process, then complete++
            if (ptr->totalTime == 0)
                complete++;
            ptr = ptr->next;
        }
        //Loop has ended, means all processes are complete
    }

};

int main() {
    CircularLinkedList list;
    int numProcesses, totalTime, quota;
    cin >> numProcesses;
    string ID;
    for (int i = 0; i < numProcesses; i++) {
        cin >> ID >> totalTime >> quota;
        list.addNodeToEnd(ID, totalTime, quota);
    }
    list.runProcesses(numProcesses);
    fflush(stdin);
    cin.get();
}
