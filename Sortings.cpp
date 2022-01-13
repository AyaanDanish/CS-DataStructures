#include <iostream>

using namespace std;

void bubbleSort(int *arr) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10 - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void insertionSort(int *arr) {
    int num;
    for (int i = 1; i < 10; i++) { // starts from the second index not the first
        num = arr[i];              // save the current array number
        int j = i - 1;             //j is the number behind the current number

        while (j >= 0 && arr[j] > num) { //while the number behind the current one is greater
            arr[j + 1] = arr[j];         //previous becomes next
            j--;                         //move comparison backwards. loop will end when j = -1
        }
        arr[j + 1] = num; //now put the current array value at index 0 (-1+1)
    }
}

void selectionSort(int *arr) {
    int smallestIndex;
    for (int i = 0; i < 10 - 1; i++) {
        smallestIndex = i;
        for (int j = i + 1; j < 10; j++) {
            if (arr[j] < arr[smallestIndex])
                smallestIndex = j;
        }
        swap(arr[i], arr[smallestIndex]);
    }
}

int getNextGap(int gap) {
    const float shrinkFactor = 1.3;
    gap = gap / shrinkFactor;
    if (gap < 1)
        return 1;
    return gap;
}

void combSort(int *arr) {
    int gap = 10;
    bool swapped = true;

    while (gap != 1 || swapped == true) {
        gap = getNextGap(gap);
        swapped = false;
        for (int i = 0; i < 10 - gap; i++) {
            if (arr[i] > arr[i + gap]) {
                swap(arr[i], arr[i + gap]);
                swapped = true;
            }
        }
    }
}


int partition(int *arr, int low, int high) {
    int pivotElement = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivotElement) {
            i++;
            swap(arr[j], arr[i]);
        }
    }
    swap(arr[high], arr[i + 1]);
    return i + 1;
}

void quickSort(int *arr, int low, int high) {
    if (low < high) {
        int pivot = partition(arr, low, high);
        quickSort(arr, low, pivot - 1);
        quickSort(arr, pivot + 1, high);
    }
}

void heapify(int *arr, int parentIndex, int size) {
    int leftIndex = 2 * parentIndex + 1;
    int rightIndex = 2 * parentIndex + 2;
    int largest = parentIndex;
    if (leftIndex < size && arr[leftIndex] > arr[largest])
        largest = leftIndex;

    if (rightIndex < size && arr[rightIndex] > arr[largest])
        largest = rightIndex;

    if (largest != parentIndex) {
        swap(arr[parentIndex], arr[largest]);
        heapify(arr, largest, size);
    }
}

void heapSort(int *arr, int index, int size) {
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(arr, i, size);

    for (int i = size - 1; i >= 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, 0, i);
    }
}

void display(int *arr) {
    for (int i = 0; i < 10; i++)
        cout << arr[i] << " ";
}

int main() {
    cout
        << "1. Bubble Sort" << endl
        << "2. Insertion Sort" << endl
        << "3. Comb Sort" << endl
        << "4. Selection Sort" << endl
        << "5. Quick Sort" << endl
        << "6. Heap Sort" << endl
        << "\nEnter a choice: ";
    int choice;
    int arr[10] = {5, 3, 8, 1, 4, 6, 2, 7, 10, 9};
    cin >> choice;
    switch (choice) {
    case 1:
        bubbleSort(arr);
        display(arr);
        break;
    case 2:
        insertionSort(arr);
        display(arr);
        break;
    case 3:
        combSort(arr);
        display(arr);
        break;
    case 4:
        selectionSort(arr);
        display(arr);
        break;
    case 5:
        quickSort(arr, 0, 9);
        display(arr);
        break;
    case 6:
        heapSort(arr, 0, 10);
        display(arr);
        break;
    }
}