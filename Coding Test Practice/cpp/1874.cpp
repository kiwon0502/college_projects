#include <iostream>
#include <stack>
#include <vector>
using namespace std;

int N;
stack<int> v;
vector<char> ans;

int main() {
  ios::sync_with_stdio(0); cout.tie(0); cin.tie(0);
  cin >> N;
  int temp = 1;
  bool flag = true;
  for (int i = 0; i < N; i++) {
    int x; cin >> x;
    if (temp <= x) {
      for (int j = temp; j <= x; j++) {
        v.push(j);
        ans.push_back('+');
      }
      temp = x + 1;
      v.pop();
      ans.push_back('-');
    }
    else {
      if (v.top() == x) {
        v.pop();
        ans.push_back('-');
      }
      else {
        flag = false;
        break;
      }
    }
  }
  if (!flag) cout << "NO";
  else {
    for (auto c : ans) {
      cout << c << "\n";
    }
  }
  return 0;
}