#include <iostream>
#include <cmath>
using namespace std;

int N, ans;
double jimin, hansoo;

int main() {
  ios::sync_with_stdio(0); cout.tie(0); cin.tie(0);
  cin >> N >> jimin >> hansoo;
  while (jimin != hansoo) {
    jimin = ceil(jimin/2);
    hansoo = ceil(hansoo/2);
    ans++;
  }
  cout << ans;
  return 0;
}