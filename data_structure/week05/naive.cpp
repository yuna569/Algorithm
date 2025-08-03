#include <iostream>
#include <string>

using namespace std;

int main(void)
{
    string text = "abababcabcabcdabccbaabdabcabccabcd";
    int num[34][7] = {0, };
    string pattern = "abcabcd";

    bool flag = false;
    int j = 0;

    for (int i=0; i<text.length(); i++) {
        if (text[i] == pattern[i-j]) {
            if (flag) { for (int k=0; k<7; k++) { if (num[i-1][k] != 0) num[i][k] = num[i-1][k] + 1;} }
            else {
                num[i][0] = 1;
                flag = true;
            }
        }
        else {
            flag = false;
            j = i;
            if (text[i] == pattern[i-j]) {
                if (flag) { for (int k=0; k<7; k++) { num[i][k] = num[i-1][k] + 1;} }
                else {
                num[i][0] = 1;
                flag = true;
                int l = 1;
                for (int k=0; k<7; k++) {
                    if (k == i-j) continue;
                    if (pattern[k] == text[i]) {
                        num[i][l] = k+1;
                    }
                }
            }
            }
        }
    }

    for (int i=0; i<text.length(); i++) {
        cout << i << ": ";
        for (int j=0; j<7; j++) {
            cout << num[i][j] << ", ";
        }
        cout << endl;
    }

    return 0;
}