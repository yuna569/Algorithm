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

// usArray
class usArray {
private:
    int arr[MAX];
    bool mark[MAX];
    int emptyListHead = -1;
    int count = 0;
    int maxIndex = 0;       // 굳이 줄일 필요가 없다! 어차피 한 번 사용했었으면 값이 남아있을 테니까
    int left, right;
public:
    usArray(int array[], int n, bool sorted);
    int searchX(int x, int& left, int& right);
    int insertX(int x);
    int deleteX(int x);
    int getValue(int i) { return arr[i]; }
    void printArray();
};

usArray::usArray(int array[], int n, bool sorted) {
    if (!sorted) { re_selection_sort(array, n); }

    for (int i=0; i<n; i++) { this->arr[i] = array[i]; }

    for (int i=0; i<n; i++) { this->mark[i] = 1; }

    count = n;
    maxIndex = n-1;
}

int usArray::searchX(int x, int& left, int& right) {
    left = 0; right = maxIndex;
    int m;

    while (left <= right) {
        m = (left + right) / 2;

        if (arr[m] == x && mark[m]) return m;
        else if (arr[m] > x) right = m-1;
        else left = m+1;
    }

    return -1;
}

int usArray::insertX(int x) {
    int left = 0, right = count - 1;
    int i = searchX(x, left, right);
    if (i != -1) return -1;
    if (count >= MAX) return -100;

    int xIndex = left;

    /* 해당 자리가 비어있으면 바로 삽입
    if (!mark[xIndex]) {
        arr[xIndex] = x; 
        mark[xIndex] = 1;
        count++;
        if (xIndex > maxIndex) maxIndex = xIndex;

        return xIndex;
    }
    */

    /* 해당 자리를 사용 중인 경우

    // 빈 자리가 없는 경우 - 따로 처리하려 했는데 어차피 양방향 탐색을 하며 O(n)이 될 것 같아 한 번에 처리하기로 함
    if (maxIndex == count-1) {
        for (int j=count++; j>xIndex; j--) {
            arr[j] = arr[j-1];
        }
        arr[xIndex] = x;
        maxIndex++;
        return xIndex;
    }
    
    // 빈 자리 탐색
    int j;
    // xIndex의 좌측 탐색
    for (j=xIndex-1; j>=0; j--) if (!mark[j]) break;
    if (j != -1) xIndex = j;
    else {  // xIndex의 우측 탐색
        for (j=xIndex+1; j<=maxIndex; j++) if (!mark[j]) break;
        if (j != maxIndex+1) xIndex = j;
    }
    
    arr[xIndex] = x;
    mark[xIndex] = 1;
    count++;
    */

    // 지피티가 양방향 한 번에 처리하는 건 어떻냐 함. 괜찮은 것 같아서 해보기로 함
    int j=0;        // 원래 1로 하려 했는데, 0부터 시작하면 자리가 비어있는 경우 따로 처리 안 해줘도 됨!
    int emptyIndex = -1;
    while(xIndex+j <= maxIndex+1 || xIndex-j >= 0) {
        if (xIndex+j<=maxIndex+1 && !mark[xIndex+j]) {
            emptyIndex = xIndex+j;
            break;
        }
        if (xIndex-j>=0 && !mark[xIndex-j]) {
            emptyIndex = xIndex-j;
            break;
        }

        j++;
    }

    if (emptyIndex == -1) {
        for (int k=count++; k>xIndex; k--) arr[k] = arr[k-1];
        arr[xIndex] = x;
        maxIndex++;
        return xIndex;
    }

    if (emptyIndex > xIndex) {
        for (int k=emptyIndex; k>xIndex; k--) arr[k] = arr[k-1];
        mark[emptyIndex] = 1;
    }
    else xIndex = emptyIndex;

    if (xIndex > maxIndex) maxIndex = xIndex;

    arr[xIndex] = x;
    mark[xIndex] = 1;
    count++;

    return xIndex;
}

int usArray::deleteX(int x) {
    int left = 0, right = maxIndex;
    int index = searchX(x, left, right);
    if (index == -1) return -1;

    mark[index] = 0;
    count--;

    if (index == maxIndex) {
        for(int i=maxIndex-1; i>=0; i--) {
            if (mark[i]) { maxIndex = i; break; }
        }
    }

    return index;
}

void usArray::printArray() {
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
    usArray Arr = usArray(arr, 10, false);
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
            int left, right;                // 필요없음
            i = Arr.searchX(x, left, right);
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