#include <iostream>
#include <ctime>

using namespace std;

// swap two element of the array
void swap(int* arr, int a, int b) {
    int t = arr[a];
    arr[a] = arr[b];
    arr[b] = t;
}

/***************************/
/* BINARY SEARCH ALGORITHM */
/***************************/
int BinarySearch(int* arr, int len, int search, bool bypass_exception = false) {
    int left = 0, right = len - 1;
    while (left <= right) {
        int pos = (left + right) / 2;
        if (search < arr[pos]) {
            right = pos - 1;
        }
        else if (search > arr[pos]) {
            left = pos + 1;
        }
        else {
            return pos;
        }
    }
    if (!bypass_exception) {
        throw domain_error("No such element in array");
    }
    return -1;
}

/************************/
/* QUICK SORT ALGORITHM */
/************************/

// partition for quicksort
int partition(int* arr, int high, int low) {
    int smaller = low - 1; // index of smaller element
    for (int i = low; i <= high - 1; i++) {
        if (arr[i] <= arr[high]) { // current element is smaller or equal to pivot
            smaller++;
            swap(arr, i, smaller);
        }
    }
    smaller++;
    swap(arr, smaller, high);
    return smaller;
}

// quicksort one step
void QuickSort_step(int* arr, int high, int low = 0) {
    if (low < high) {
        int prt_index = partition(arr, high, low);
        QuickSort_step(arr, high, prt_index + 1); // separately sort right part
        QuickSort_step(arr, prt_index - 1, low); // separately sort left part
    }
}

// QUICK SORT ALGORITHM
void QuickSort(int* arr, int len) {
    QuickSort_step(arr, len - 1);
}

/*************************/
/* BUBBLE SORT ALGORITHM */
/*************************/
void BubbleSort(int* arr, int len) {
    bool changed = true; // weither something was changed on the last iteration or not
    int passed = 0; // how many iterations was already passed
    while (changed) {
        changed = false;
        for (int i = 0; i < len - passed - 1; i++) {
            if (arr[i] > arr[i + 1]) { // if order isn't correct
                swap(arr, i, i + 1);
                changed = true;
            }
        }
    }
}

/***********************/
/* BOGO SORT ALGORITHM */
/***********************/

// shuffle the array
void shuffle(int* arr, int len) {
    for (int i = 0; i < len; i++) {
        int random = rand() % len;
        swap(arr, i, random);
    }
}

// check if array is sorted
bool is_sorted(int* arr, int len) {
    for (int i = 0; i < len - 1; i++) {
        if (arr[i] > arr[i + 1]) { // if order isn't correct
            return false;
        }
    }
    return true;
}

// BOGO SORT ALGORITHM
void BogoSort(int* arr, int len) {
    while (!is_sorted(arr, len)) {
        shuffle(arr, len);
    }
}

/***************************/
/* COUNTING SORT ALGORITHM */
/***************************/
void CountingSort(unsigned char* arr, int len) {
    const int clen = UCHAR_MAX; // counter array length - unsigned char can be from 0 to 255
    int* counter = new int[clen]; // counter for every character
    for (unsigned char i = 0; i < clen; i++) {
        counter[i] = 0;
    }
    for (int i = 0; i < len; i++) {
        counter[arr[i]]++; // increment counter for current character
    }
    int pos = 0; // current position in char array
    for (unsigned char i = 0; i < clen; i++) { // for every character
        for (int count = 0; count < counter[i]; count++, pos++) { // repeat counter[i] times
            arr[pos] = i; // add this character on the current position
        }
    }
}

// time counter
void time_counter(const int size) {
    const int number_of_tests = 10;
    int** test_data_1 = new int*[number_of_tests]; // 10 arrays for QuickSort
    int** test_data_2 = new int*[number_of_tests]; // the same 10 arrays for BubbleSort
    for (int test_number = 0; test_number < number_of_tests; test_number++) { // fullfill arrays with random data
        test_data_1[test_number] = new int[size];
        test_data_2[test_number] = new int[size];
        for (int i = 0; i < size; i++) {
            int n = rand();
            test_data_1[test_number][i] = n;
            test_data_2[test_number][i] = n;
        }
    }
    clock_t qs_begin = clock();
    for (int test_number = 0; test_number < number_of_tests; test_number++) { // testing of QuickSort
        QuickSort(test_data_1[test_number], size);
    }
    clock_t qs_end = clock();
    clock_t bs_begin = clock();
    for (int test_number = 0; test_number < number_of_tests; test_number++) { // testing of QuickSort
        BubbleSort(test_data_2[test_number], size);
    }
    clock_t bs_end = clock();
    double qs_ms = double(qs_end - qs_begin) / number_of_tests; // average (ms) for QuickSort
    double bs_ms = double(bs_end - bs_begin) / number_of_tests; // average (ms) for BubbleSort
    if (qs_ms > 1000000 || bs_ms >= 1000000) {
        printf("Size: %d\t\tQuickSort: %8.2e ms\t\tBubbleSort: %8.2e ms\n", size, qs_ms, bs_ms);
    }
    else {
        printf("Size: %d\t\tQuickSort: %8.1f ms\t\tBubbleSort: %8.1f ms\n", size, qs_ms, bs_ms);
    }
}

int main()
{
    time_counter(10);
    time_counter(100);
    time_counter(1000);
    time_counter(10000);
    time_counter(100000);
}
