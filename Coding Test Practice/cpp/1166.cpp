#include <iostream>
using namespace std;
using ll = long long;

int N, L, W, H;

bool solve(long double mid) {
  ll a1 = (ll)((long double)L/mid);
  ll a2 = (ll)((long double)W/mid);
  ll a3 = (ll)((long double)H/mid);
  if (a1 * a2 * a3 < N) return false;
  return true;
}

long double bs() {
  long double left = 0;
  long double right = 1e15;

  for (int i = 0; i < 10000; i++) {
    long double mid = (left + right) / 2;
    if (solve(mid)) left = mid;
    else right = mid;
  }
  return right;
}

int main() {
  double left = 0, right = 1000000000, mid;
  cin >> N >> L >> W >> H;
  printf("%.10Lf", bs());
  return 0;
}