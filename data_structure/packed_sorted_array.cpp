#include <iostream>
#define MAX 100

using namespace std;

void re_selection_sort(int arr[], int n) {
    if (n == 1) return;

    int min = 0;
    for (int i=1; i<n; i++) {
        if (arr[i] < arr[min]) min = i;
    }
    int temp = arr[0];
    arr[0] = arr[min];
    arr[min] = temp;

    re_selection_sort(arr+1, n-1);
}

bool re_binary_search_v1(int arr[], int n, int x) {
    if (n == 0) return false;

    int m = (n-1) / 2;

    if (arr[m] == x) return true;
    else if (arr[m] > x) return re_binary_search_v1(arr, m, x);
    else return re_binary_search_v1(arr+m+1, n-(m+1), x);
}

int re_binary_search_v2(int arr[], int n, int x) {
    if (n == 0) return 0;

    int m = (n-1) / 2;

    if (arr[m] == x) return m;
    else if (arr[m] > x) return re_binary_search_v2(arr, m, x);
    else return re_binary_search_v2(arr+m+1, n-(m+1), x) + (m+1);       // 찾는 원소가 없을 때에도, 있다면 있어야 할 인덱스 반환
}

class psArray {
private:
    int arr[MAX];
    int count = 0;
public:
    psArray(int array[], int n, bool sorted);
    int searchX(int x);
    int insertX(int x);
    int deleteX(int x);
    int getValue(int i) { return arr[i]; }
    void printArray();
};

psArray::psArray(int array[], int n, bool sorted) {
    if (!sorted) { re_selection_sort(array, n); }

    for (int i=0; i<n; i++) { this->arr[i] = array[i]; }

    count = n;
}

int psArray::searchX(int x) {
    if (!re_binary_search_v1(arr, count, x)) return -1;
    return re_binary_search_v2(arr, count, x);
}

int psArray::insertX(int x) {
    if (re_binary_search_v1(arr, count, x)) return -1;
    if (count >= MAX) return -100;

    int i = re_binary_search_v2(arr, count, x);

    /*
        주의: 있어야 한다면 i 인덱스에 있어야 한다! 가 binary search의 결과
        그치만 그 i에 있는 원소가, 내가 넣고 싶은 값보다 큰지 작은지 모름 - 가장 마지막에 옮겨졌을 끝 인덱스가 left일지 right일지 모르기 때문!
        즉, 가장 마지막으로 비교했던 원소가 내가 찾던 값보다 컸을지 작았을지 모름 -> 따져줘야 됨
        ex. 배열 23 45 67 에
            1. 56 넣는 경우
            2. 34 넣는 경우
    */
    int xIndex;
    if (arr[i] > x) xIndex = i;
    else xIndex = i+1;     // arr[i] < x

    // 초기 진입할 시 j=count 후, count 한 번만 증가
    // x가 들어갈 위치에 존재하는 원소까지만 한 칸 이동
    for (int j=count++; j>xIndex; j--) {
        arr[j] = arr[j-1];
    }
    arr[xIndex] = x;

    return xIndex;
}

int psArray::deleteX(int x) {
    int index = searchX(x);
    if (index == -1) return -1;
    // if (count <= 0) return -1;

    for (int i=index; i<count-1; i++) {
        arr[i] = arr[i+1];
    }
    arr[count-1] = -100;
    count--;
    return index;
}

void psArray::printArray() {
    for (int i=0; i<count; i++) {
        cout << i << '\t';
    }
    cout << endl;
    for (int i=0; i<count; i++) {
        cout << arr[i] << '\t';
    }
    cout << endl;
}

int main(void) {
    int arr[10] = { 2, 45, 12, 89, 23, 32, 76, 94, 61, 58};
    psArray Arr = psArray(arr, 10, false);
    char c;
    int x;
    int i;

    while(true) {
        cout << "------------------------------------------------------------" << endl;
        Arr.printArray();
        cout << endl;

        cout << "Menu (s, i, d, q): ";
        cin >> c;
        if (c == 's') {
            cout << "Search: ";
            cin >> x;
            i = Arr.searchX(x);
            if (i == -1) {
                cout << x << " Not Found" << endl;
            } 
            else {
                cout << x << " Found at " << "Arr[" << i << "]" << endl;
            }
        }
        else if (c == 'i') {
            cout << "Insert: ";
            cin >> x;
            i = Arr.insertX(x);
            if (i == -1) {
                cout << x << " Already in Arr" << endl;
            }
            else if (i == -100) {
                cout << "Array Full" << endl;
            }
            else {
                cout << x << " Inserted in " << "Arr[" << i << "]" << endl;
            }
        }
        else if (c == 'd') {
            cout << "Delete: ";
            cin >> x;
            i = Arr.deleteX(x);
            if (i == -1) {
                cout << x << " Not In Arr" << endl;
            }
            else {
                cout << x << " Deleted" << endl;
            }
        }
        else if (c == 'q') {
            cout << "Good Bye" << endl;
            break;
        }
        else {
            cout << "Wrong Command" << endl;
        }
        cout << "------------------------------------------------------------" << endl;
        cout << endl;
    }
    cout << "------------------------------------------------------------" << endl;

    return 0;
}