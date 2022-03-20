#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n;
vector<int> v;

int main() {
  ios::sync_with_stdio(0); cout.tie(0); cin.tie(0);
  cin >> n;
  for (int i = 0; i < n; i++) {
    int x; cin >> x;
    if (v.empty() || v.back() < x) v.push_back(x);
    else {
      *lower_bound(v.begin(), v.end(), x) = x;
    }
  }
  cout << v.size();
  return 0;
}