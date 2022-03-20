#include <iostream>
#include <algorithm>
#include <string>
typedef long long ll;
using namespace std;

ll N, ans, alpha[10], t[10];
string s[50];
bool initial[10];
pair<ll, int> b[10];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>N;
    for (int i = 0; i < N; i++) {
        cin>>s[i];
        ll idx = 1;
        for (int j = s[i].size() - 1; j >= 0; j--) {
            alpha[s[i][j] - 'A'] += idx;
            idx *= 10;
        }
        initial[s[i][0] - 'A'] = true;
    }
    for (int i = 0; i < 10; i++) b[i] = {alpha[i], i};
    sort(b, b + 10);

    if (b[0].first != 0 && initial[b[0].second]) {
        int idx = 1;
        for( ; ;idx++) if (!initial[b[idx].second]) break;
        auto tmp = b[idx];
        for(int i = idx - 1; i >= 0; i--) b[i + 1] = b[i];
        b[0] = tmp;
    }

    for(int i = 9, j = 9; i >= 0; i--, j--){
        if (b[i].first == 0) break;
        t[b[i].second] = j;
    }

    for(int i = 0; i < N; i++){
        string str = s[i], ret;
        for(int j = 0; j < str.size(); j++) ret += t[str[j] - 'A'] + '0';
        ans += stoll(ret);
    }
    cout<<ans;
    return 0;
}