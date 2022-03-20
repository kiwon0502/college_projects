#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

string in;

vector<int> Fail(string pattern) {
    int m = pattern.size();
    vector<int> pi(m);
    pi[0] = 0;
    for (int i = 1, j = 0; i < m; i++) {
        while (j > 0 && pattern[i] != pattern[j]) {j = pi[j - 1];}
        if (pattern[i] == pattern[j]) pi[i] = ++j;
    }
    return pi;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> in;

    return 0;
}
