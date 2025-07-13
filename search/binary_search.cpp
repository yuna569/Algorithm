#include <iostream>

using namespace std;

int binary_search(int arr[], int n, int x) {
    int l, r, m;

    l = 0;
    r = n - 1;

    cout << "l, r: " << l << ", " << r << endl;
    
    while (l <= r) {        // 등호를 넣어야 하는가? - l이랑 r이랑 같아지는 경우: 직전에 m이 1) l보다 한 칸 컸을 때 2) r보다 한 칸 작았을 때 / 근데 1인 경우랑 2인 경우랑 사실상 같음! 등호를 포함하느냐는 l이랑 r이 같아지기 직전에, l 또는 r을 검사했느냐에 따라 결정되는데 안 했을 가능성이 있음. 따라서 포함해야 함 -> 끝 원소를 찾을 때 필요하다 함! 
        m = (l + r) / 2;
        cout << "l, r, m: " << l << ", " << r << ", " << m << endl;
        cout << "arr[m]: " << arr[m] << endl;

        if (arr[m] == x) return m;
        
        if (arr[m] < x) l = m + 1;      //  왜 m으로 안 할까? 란 생각을 함. 근데 그럼 l==m 또는 r==m이 되는 경우 무한 루프 발생
        else if (arr[m] > x) r = m - 1;
    }
    return -100;
}

// 인덱스 반환
int recursive_binary_search_v1(int arr[], int n, int x) {
    cout << "arr: " << arr << " n: " << n << endl;
    if (n==0) return -100;      // base         // 1로 하면 확인 못하는 원소가 생길 수도?!

    int l, r, m;
    l = 0; r = n - 1;
    m = (l + r) / 2;

    if (arr[m] == x) return m;
    else if (arr[m] > x) return recursive_binary_search_v1(arr, m, x);
    else {  // if (arr[m] < x) 
        int result = recursive_binary_search_v1(arr + m + 1, n - (m + 1), x);
        if (result == -100) return result;
        return result + m + 1;      // m+1을 더하므로, -1이 반환될 때, 최종적으로 -1이 반환되지 않음 - 처리 필요
    }
}

// 존재 여부 반환
bool recursive_binary_search_v2(int arr[], int n, int x) {
    cout << "arr: " << arr << " n: " << n << endl;
    if (n==0) return false;      // base

    int l, r, m;
    l = 0; r = n - 1;
    m = (l + r) / 2;

    if (arr[m] == x) return true;
    else if (arr[m] > x) return recursive_binary_search_v2(arr, m, x);
    else return recursive_binary_search_v2(arr + m + 1, n - (m + 1), x);
}

int main(void)
{
    int arr[10] = {9, 12, 24, 35, 48, 51, 63, 72, 88, 97};
    int x = 52;

    // int i = binary_search(arr, sizeof(arr) / sizeof(int), x);
    // int i = recursive_binary_search_v1(arr, sizeof(arr) / sizeof(int), x);
    bool b = recursive_binary_search_v2(arr, sizeof(arr) / sizeof(int), x);
    
    // cout << "arr[" << i << "]: " << arr[i] << endl;
    cout << x << " is in arr? " << b << endl;

    return 0;
}