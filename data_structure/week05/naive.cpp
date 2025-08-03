#include <iostream>
#include <string>

using namespace std;

int main(void)
{
    string text = "abababcabcabcdabccbaabdabcabcdabcd";
    int num[34][2] = {0, };
    string pattern = "abcabcd";

    bool flag = false;
    int j = 0;
    int k = 0;

    for (int i=0; i<text.length(); i++) {
        for (int j=0; j<7; j++) {
            if (text[i+j] == pattern[j]) {
                if (num[i+j][0]!=0) {
                    num[i+j][1] = j+1;
                }
                else num[i+j][0] = j+1;
            }
            else break;
        }
    }

    for (int i=0; i<text.length(); i++) {
        cout << i << ": ";
        for (int j=0; j<2; j++) {
            cout << num[i][j] << ", ";
        }
        cout << endl;
    }

    return 0;
}