#include <iostream>
#define MAX 100

using namespace std;

class puArray {
private:
    int arr[MAX];
    int count = 0;
public:
    puArray(int array[], int n);
    int searchX(int x);
    int insertX(int x);
    int deleteX(int x);
    int getValue(int i) { return arr[i]; }
    void printArray();
};

puArray::puArray(int array[], int n) {
    for (int i=0; i<n; i++) {
        this->arr[i] = array[i];
    }
    count = n;
}

int puArray::searchX(int x) {
    for (int i=0; i<count; i++) {
        if (arr[i] == x) return i;
    }
    return -1;
}

int puArray::insertX(int x) {
    if (searchX(x) != -1) return -1;
    if (count >= MAX) return -100;

    arr[count++] = x;

    return count-1;
}

int puArray::deleteX(int x) {
    int index = searchX(x);
    if (index == -1) return -1;
    // if (count <= 0) return -1;

    arr[index] = arr[--count];

    return index;
}

void puArray::printArray() {
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
    puArray Arr = puArray(arr, 10);
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