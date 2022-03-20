#include <iostream>
#define ll long long int
using namespace std;

ll N, K, ans;
bool alphabet[26];
string s[51];

ll find_wordnum() {
    ll count = 0;
    for (ll i=1; i<=N; i++) {
        bool flag = true;
        for (ll j=0; j<s[i].length(); j++) {
            if (!alphabet[s[i][j] - 'a']) {
                flag = false;
                count++;
                break;
            }
        }
    }
    return N - count;
}

void sim(ll start, ll count) {
    if (count == K-5) {
        ll num = find_wordnum();
        if (ans < num) ans = num;
        return;
    }
    for (ll i = start; i < 26; i++) {
        if (alphabet[i]) continue;
        alphabet[i] = true;
        sim(i + 1, count + 1);
        alphabet[i] = false;
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>N>>K;
    for (ll i=1; i<=N; i++) {
        string str;
        cin>>str;
        s[i] = str.substr(4, (str.length() - 8));
    }

    if (K == 26) {
        ans = N;
    }
    else if (K >= 5){
        alphabet['a' - 'a'] = true;
        alphabet['c' - 'a'] = true;
        alphabet['i' - 'a'] = true;
        alphabet['n' - 'a'] = true;
        alphabet['t' - 'a'] = true;
        sim(0, 0);
    }
    cout<<ans;
    return 0;
}