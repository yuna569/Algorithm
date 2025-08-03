#include <iostream>
#define MAX 100

using namespace std;

class uuArray {
private:
    int arr[MAX];
    bool mark[MAX];
    int emptyListHead = -1;
    int count = 0;
    int maxIndex = 0;
public:
    uuArray(int array[], int n);
    int searchX(int x);
    int insertX(int x);
    int deleteX(int x);
    int getValue(int i) { return arr[i]; }
    void printArray();
};

uuArray::uuArray(int array[], int n) {
    for (int i=0; i<n; i++) {
        this->arr[i] = array[i];
    }
    for (int i=0; i<n; i++) {
        this->mark[i] = 1;
    }
    count = n;
    maxIndex = n-1;
}

int uuArray::searchX(int x) {
    for (int i=0; i<=maxIndex; i++) {
        if (mark[i] && arr[i] == x) return i;
    }
    return -1;
}

int uuArray::insertX(int x) {
    if (searchX(x) != -1) return -1;
    if (count >= MAX) return -100;

    // for (int i=0; i<maxIndex; i++) {
    //     if (!mark[i]) arr[i] = x;
    // }
    if (emptyListHead == -1) {
        arr[count] = x;
        mark[count] = 1;

        count++;
        maxIndex++;

        return count-1;
    }
    int temp = arr[emptyListHead];
    int index = emptyListHead;

    arr[index] = x;
    mark[index] = 1;
    emptyListHead = temp;

    return index;
}

int uuArray::deleteX(int x) {
    int index = searchX(x);
    if (index == -1) return -1;

    mark[index] = 0;
    arr[index] = emptyListHead;
    emptyListHead = index;
    count--;

    if (index == maxIndex) {
        for(int i=maxIndex-1; i>=0; i--) {
            if (mark[i]) { maxIndex = i; break; }
        }
    }

    return index;
}

void uuArray::printArray() {
    for (int i=0; i<=maxIndex; i++) {
        cout << i << '\t';
    }
    cout << endl;
    for (int i=0; i<=maxIndex; i++) {
        cout << arr[i] << '\t';
    }
    cout << endl;
    for (int i=0; i<=maxIndex; i++) {
        char check = 'X';
        if (mark[i]) check = 'O';
        cout << check << '\t';
    }
    cout << endl;
}

int main(void) {
    int arr[10] = { 2, 45, 12, 89, 23, 32, 76, 94, 61, 58};
    uuArray Arr = uuArray(arr, 10);
    char c;
    int x;
    int i;

    while(true) {
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
            Arr.deleteX(x);
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
        cout << endl;
    }

    return 0;
}