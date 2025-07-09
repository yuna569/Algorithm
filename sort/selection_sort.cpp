#include <iostream>

using namespace std;

// 탐색하며 가장 작은 값 추출 후 자리 교환
void selection_sort(int arr[], int n) {
    int min;

    for (int i=0; i<n; i++) {
        min = i;
        for (int j=i+1; j<n; j++) {
            if (arr[min] > arr[j]) {
                min = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
    }
}

void recursive_selection_sort(int arr[], int n) {
    if (n == 0) return;

    int min = 0;
    for (int i=1; i<n; i++) {
        if (arr[min] > arr[i]) min = i;
    }

    int temp = arr[0];
    arr[0] = arr[min];
    arr[min] = temp;

    recursive_selection_sort(arr + 1, n - 1);
}

int main(void)
{
    int arr[10] = {26, 72, 39, 12, 56, 68, 99, 2, 87, 45};
    int size = sizeof(arr) / sizeof(int);

    recursive_selection_sort(arr, size);

    for (int i=0; i<size; i++) {
        cout << arr[i] << '\t';
    }

    return 0;
}