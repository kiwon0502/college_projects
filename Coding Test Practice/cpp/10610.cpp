#include <iostream>
using namespace std;

char s[100001];
int sum, Count[128];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>s;
    for (int i = 0; s[i]; i++) {
        sum += s[i] - '0';
        Count[s[i]]++;
    }

    if (sum%3 != 0 || Count['0'] == 0) {
        cout<<"-1";
        return 0;
    }

    for (int i = '9'; i >= '0'; i--) {
        for (int j = 0; j < Count[i]; j++) {
            cout<<i - '0';
        }
    }
    return 0;
}