#include <iostream>

using namespace std;

int linear_search(int arr[], int x) {
    for (int i=0; i<sizeof(arr)/sizeof(int); i++) {
        if (*(arr+i) == x) return i;
    }
    return -1;
}

int main(void)
{
    int arr[10] = {9, 12, 24, 35, 48, 51, 63, 72, 88, 97};
    int x = 24;
    

    return 0;
}