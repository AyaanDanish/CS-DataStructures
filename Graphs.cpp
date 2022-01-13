#include <iostream>
#include <list>
#include <queue>
#include <stack>
using namespace std;

class Node {
public:
    int data;
    Node *next;

    Node(int data) {
        this->data = data;
        next = NULL;
    }
};

class Graph {
public:
    int numOfNodes;
    Node **adjList; // Dynamic pointer array
    int **adjArr;   // Dynamic int array
    Graph(int numOfNodes) {
        this->numOfNodes = numOfNodes;
        adjList = new Node *[numOfNodes];
        adjArr = new int *[numOfNodes];
        for (int i = 0; i < numOfNodes; i++) {
            adjList[i] = NULL;                  // Each subscript contains a pointer to a LL
            adjArr[i] = new int[numOfNodes]{0}; // Each subscript contains a 1D array
        }
    }

    void addEdge(int firstNode, int secondNode) {
        // Inserting into the List
        Node *firstNewNode = new Node(firstNode);
        Node *secondNewNode = new Node(secondNode);
        insert(firstNewNode, secondNode);
        insert(secondNewNode, firstNode);

        // Inserting into the matrix
        adjArr[firstNode][secondNode] = 1;
        adjArr[secondNode][firstNode] = 1;
    }

    void insert(Node *newNode, int nodeIndex) {
        if (adjList[nodeIndex] == NULL) {
            adjList[nodeIndex] = newNode;
            return;
        }
        if (newNode->data < adjList[nodeIndex]->data) {
            newNode->next = adjList[nodeIndex];
            adjList[nodeIndex] = newNode;
            return;
        }

        Node *ptr = adjList[nodeIndex];
        while (ptr->next != NULL && ptr->next->data < newNode->data)
            ptr = ptr->next;

        newNode->next = ptr->next;
        ptr->next = newNode;
    }

    void displayList() {
        cout << "Adjacency List: " << endl;
        for (int i = 0; i < numOfNodes; i++) {
            if (adjList[i] == NULL) {
                cout << i << "|-> NULL" << endl;
                continue;
            }
            Node *ptr = adjList[i];
            cout << i << "|";
            while (ptr != NULL) {
                cout << "-> " << ptr->data << " ";
                ptr = ptr->next;
            }
            cout << endl;
        }
        cout << endl;
    }

    void displayMatrix() {
        cout << "Adjacency Matrix:\n  ";
        for (int i = 0; i < numOfNodes; i++)
            cout << i << " ";
        cout << endl;
        for (int i = 0; i < numOfNodes; i++) {
            cout << i << " ";
            for (int j = 0; j < numOfNodes; j++)
                cout << adjArr[i][j] << " ";
            cout << endl;
        }
        cout << endl;
    }

    void BFSMatrix(int start) {
        bool *visited = new bool[numOfNodes]{false};
        queue<int> q;

        visited[start] = true;
        q.push(start);

        while (!q.empty()) {
            int front = q.front();
            q.pop();
            cout << front << " ";

            for (int col = 0; col < numOfNodes; col++) {
                if (adjArr[front][col] == 1 && visited[col] == false) {
                    visited[col] = true;
                    q.push(col);
                }
            }
        }
        cout << endl;
    }

    void BFSList(int start) {
        bool *visited = new bool[numOfNodes]{false};
        queue<int> q;

        visited[start] = true;
        q.push(start);

        while (!q.empty()) {
            int front = q.front();
            q.pop();
            cout << front << " ";

            Node *ptr = adjList[front];
            while (ptr != NULL) {                  // Traverse the adjacency list of the newly popped item
                if (visited[ptr->data] == false) { // If an item in the list is unvisited, mark it as visited and enqueue it
                    visited[ptr->data] = true;
                    q.push(ptr->data);
                }
                ptr = ptr->next;
            }
        }
        cout << endl;
    }

    void DFSList(int start) {
        bool *visited = new bool[numOfNodes]{false};
        stack<int> stk;

        visited[start] = true;
        stk.push(start);

        while (!stk.empty()) {
            int top = stk.top();
            stk.pop();
            cout << top << " ";

            Node *ptr = adjList[top];
            while (ptr != NULL) {                  // Traverse the adjacency list of the newly popped item
                if (visited[ptr->data] == false) { // If an item in the list is unvisited, mark it as visited and push it
                    visited[ptr->data] = true;
                    stk.push(ptr->data);
                }
                ptr = ptr->next;
            }
        }
        cout << endl;
    }

    void DFSMatrix(int start) {
        bool *visited = new bool[numOfNodes]{false};
        stack<int> stk;

        visited[start] = true;
        stk.push(start);

        while (!stk.empty()) {
            int top = stk.top();
            stk.pop();
            cout << top << " ";

            for (int col = 0; col < numOfNodes; col++) {
                if (adjArr[top][col] == 1 && visited[col] == false) {
                    visited[col] = true;
                    stk.push(col);
                }
            }
        }
        cout << endl;
    }
};

int main() {
    Graph gph(5);
    gph.addEdge(0, 1);
    gph.addEdge(1, 3);
    gph.addEdge(3, 4);
    gph.addEdge(0, 4);
    gph.addEdge(1, 4);
    gph.addEdge(2, 1);
    gph.addEdge(2, 3);
    gph.displayMatrix();
    gph.displayList();
    gph.DFSList(0);
    gph.DFSMatrix(0);
}