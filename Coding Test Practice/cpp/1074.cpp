#include <iostream>
#include <cmath>
using namespace std;

int n, r, c;
int ans = 0;

bool check(int x, int m) {
    if (x <= pow(2, m-1)) return false;
    else return true;
}

void slice(int x, int y) {
    if (n < 1) return;
    if (check(x, n)) {
        x -= pow(2, n-1);
        ans += pow(pow(2, n-1),2) * 2;
    }
    if (check(y, n)) {
        y -= pow(2, n-1);
        ans += pow(pow(2, n-1),2);
    }
    n--;
    slice(x, y);
}

int main() {
    cin>>n>>r>>c;
    slice(r+1, c+1);
    cout<<ans;
    return 0;
}