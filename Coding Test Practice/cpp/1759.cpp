#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
using namespace std;

int L, C;
char X[15];
bool alpha[26];

void dfs(string s, int now, int depth) {
    if (depth == L) {
        int cons = 0, vowel = 0;
        for (int i = 0; i < s.length(); i++) {
            if (alpha[s[i] - 'a']) cons++;
            else vowel++;
        }

        if (cons >= 2 && vowel >= 1) cout<<s<<"\n";
        return;
    }

    for (int i = now + 1; i <= C - L + depth; i++) {
        dfs(s + X[i], i, depth + 1);
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    memset(alpha, true, sizeof(alpha));
    alpha['a' - 'a'] = false;
    alpha['e' - 'a'] = false;
    alpha['i' - 'a'] = false;
    alpha['o' - 'a'] = false;
    alpha['u' - 'a'] = false;

    cin>>L>>C;
    for (int i = 0; i < C; i++) cin>>X[i];
    sort(X, X + C);

    string s  = "";
    for (int i = 0; i <= C - L; i++) {
        dfs(s + X[i], i, 1);
    }
    return 0;
}