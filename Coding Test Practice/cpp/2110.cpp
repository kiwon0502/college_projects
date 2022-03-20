#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, C;
vector<int> x;

int main() {
  ios::sync_with_stdio(0); cout.tie(0); cin.tie(0);
  cin >> N >> C;
  for (int i = 0; i < N; i++) {
    int temp; cin >> temp;
    x.push_back(temp);
  }
  sort(x.begin(), x.end());

  int left = 0;
  int right = x[N - 1];

  while (left <= right) {
    int mid = (left + right) / 2;
    int cnt = 1, pre = 0;
    for (int cur = 1; cur < N; cur++) {
      if (x[cur] - x[pre] >= mid) {
        pre = cur;
        cnt++;
      }
    }
    if (cnt >= C) left = mid + 1;
    else right = mid - 1;
  }
  cout << right;
  return 0;
}