#include <iostream>

using namespace std;

int* merge_two_sorted_array(int arr1[], int arr2[], int n1, int n2) {
    int* arr = new int[n1+n2];
    
    int idx = 0, idx1 = 0, idx2 = 0;
    
    while (idx1 < n1 || idx2 < n2) {
        if (idx1 == n1) { arr[idx++] = arr2[idx2++]; continue; }
        if (idx2 == n2) { arr[idx++] = arr1[idx1++]; continue; }

        if (arr1[idx1] <= arr2[idx2]) arr[idx++] = arr1[idx1++];
        else if (arr1[idx1] > arr2[idx2]) arr[idx++] = arr2[idx2++];
    }

    return arr;
}

// 새로운 배열에 복사해서 거기서 정렬해야된다는데 무슨 차이지? merge를 진행한 배열을 명시적으로 생성하냐 마느냐인가?
int* recursive_merge_sort(int arr[], int n) {
    if (n == 1) {
        int* temp = new int[1];
        temp[0] = arr[0];
        return temp;
    }

    int* arr1 = recursive_merge_sort(arr, n/2);
    int* arr2 = recursive_merge_sort(arr+n/2, n-n/2);

    arr = merge_two_sorted_array(arr1, arr2, n/2, n-n/2);

    delete[] arr1;
    delete[] arr2;

    return arr;
}


int main(void)
{
    int arr[10] = {26, 72, 39, 12, 56, 68, 99, 2, 87, 45};
    int size = sizeof(arr) / sizeof(int);

    // int arr1[5] = {9, 12, 51, 63, 97};
    // int arr2[5] = {24, 35, 48, 72, 88};
    // int* arr = merge_two_sorted_array(arr1, arr2, 5, 5);

    int* arr0 = recursive_merge_sort(arr, 10);

    for (int i=0; i<10; i++) {
        cout << arr0[i] << '\t';
    }

    return 0;
}