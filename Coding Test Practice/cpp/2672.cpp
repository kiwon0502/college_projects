#include <iostream>
#include <regex>
using namespace std;

int main() {
  ios::sync_with_stdio(0); cout.tie(0); cin.tie(0);
  string s; cin >> s;
  regex re("(100+1+|01)+");
  if (regex_match(s, re)) cout << "SUBMARINE";
  else cout << "NOISE";
  return 0;
}