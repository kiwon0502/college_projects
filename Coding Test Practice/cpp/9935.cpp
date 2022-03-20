#include <iostream>
#include <string>
using namespace std;

string ans, text, bomb;

int main() {
  ios::sync_with_stdio(0); cout.tie(0); cin.tie(0);
  cin >> text >> bomb;
  int blen = bomb.size();

  for (char c : text) {
    ans += c;
    if (ans.size() < blen) continue;
    if (c == bomb.back()) {
      if (ans.substr(ans.size() - blen, blen) == bomb) {
        ans.erase(ans.size() - blen, blen);
      }
    }
  }
  if (ans.size() == 0) cout << "FRULA";
  else cout << ans;
  return 0;
}