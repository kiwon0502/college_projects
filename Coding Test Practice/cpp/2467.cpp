#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define MAX 100005
int N;
vector<int> sol(MAX);

int main() {
  ios::sync_with_stdio(0); cout.tie(0); cin.tie(0);
  cin >> N;
  sol.resize(N);
  for (int i = 0; i < N; i++) cin >> sol[i];
  int left = 0, right = N-1;
  int res = abs(sol[left] + sol[right]);
  int resA = sol[left], resB = sol[right];

  while(left < right) {
    int tmp = sol[left] + sol[right];
    if (abs(tmp) < res) {
      res = abs(tmp);
      resA = sol[left];
      resB = sol[right];
    }

    if (tmp < 0) left++;
    else right--;
  }
  cout << resA << " " << resB;
  return 0;
}