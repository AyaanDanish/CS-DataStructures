#include <iostream>
using namespace std;

class DSA {
private:
    int rows;
    int cols;
    int **arr;

public:
    DSA() {
        rows = 0;
        cols = 0;
        arr = 0;
    }

    DSA(int rows, int cols) {
        this->rows = rows;
        this->cols = cols;
        arr = new int *[rows];
        for (int i = 0; i < rows; i++) {
            arr[i] = new int[cols];
        }
    }

    DSA(const DSA &source) {
        rows = source.rows;
        cols = source.cols;
        arr = new int *[rows];
        for (int i = 0; i < rows; i++) {
            arr[i] = new int[cols];
            memcpy(arr[i], source.arr[i], sizeof(int) * cols);
        }
    }

    ~DSA() {
        for (int i = 0; i < rows; i++) {
            delete arr[i];
            arr[i] = NULL;
        }
        delete[] arr;
        arr = NULL;
    }

    void fillArray() {
        cout << "Enter " << cols << " arrays: " << endl;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cin >> arr[i][j];
            }
        }
        cout << "Array filled." << endl;
    }

    void printArray() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << arr[i][j] << " ";
            }
            cout << endl;
        }
    }

    DSA &operator=(DSA &rhs) {
        if (this == &rhs) {
            cout << "Returning this" << endl;
            return *this;
        }

        for (int i = 0; i < rows; i++) {
            delete arr[i];
            arr[i] = NULL;
        }
        delete[] arr;
        arr = NULL;

        rows = rhs.rows;
        cols = rhs.cols;
        arr = new int *[rows];
        for (int i = 0; i < rows; i++) {
            arr[i] = new int[cols];
            memcpy(arr[i], rhs.arr[i], sizeof(int) * cols);
        }
        return *this;
    }

    int &operator()(int i, int j) {
        if (i < 0 || i > rows - 1 || j < 0 || j > cols - 1) {
            cout << "Out of bounds." << endl;
            exit(1);
        }
        return arr[i][j];
    }
};

int main() {
    cout << "Enter rows and cols for array: ";
    int rows, cols;
    cin >> rows >> cols;
    DSA arr(rows, cols);
    arr.fillArray();
    DSA arr2(3, 3);
    arr2 = arr;
    arr2.printArray();
    pause();
}
