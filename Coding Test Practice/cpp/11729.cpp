#include <iostream>
using namespace std;
void move(int n, int from, int to, int bypass) {
  if (n == 1) cout << from << " " << to << "\n";
  else {
    move(n-1, from, bypass, to);
    cout << from << " " << to << "\n";
    move(n-1, bypass, to, from);
  }
}

int main() {
  ios::sync_with_stdio(0); cout.tie(0); cin.tie(0);
  int N; cin >> N;
  cout << (1<<N)-1 << "\n";
  move(N, 1, 3, 2);
  return 0;
}