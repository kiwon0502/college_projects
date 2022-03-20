#include <iostream>
#include <string>
using namespace std;
string L, R;
int ans;
bool sflag, _8flag;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>L>>R;
    int Ll = L.length();
    int Rl = R.length();

    if (Ll != Rl) ans = 0;
    else {
        for (int i = 0; i < Ll; i++) {
            if (L[i] == R[i] && L[i] == '8') {
                ans++;
            }
            else if (L[i] != R[i]) break;
        }
    }
    cout<<ans;
    return 0;
}