#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
#define MAX 101

int r, c, k, ans;
int rnum = 3, cnum = 3;
int A[MAX][MAX];
int num_cnt[MAX];

int main() {
  ios::sync_with_stdio(0); cout.tie(0); cin.tie(0);
  cin >> r >> c >> k;
  for (int i = 1; i <= 3; i++) for (int j = 1; j <= 3; j++) cin >> A[i][j];
  bool flag = false;
  for (ans = 0; ans <= 100; ans++) {
    if (A[r][c] == k) {flag = true; break;}
    vector<int> rcnum;

    if (rnum >= cnum) {
      for (int i = 1; i <= rnum; i++) {
        vector<pair<int, int>> v;
        int idx = 0;

        memset(num_cnt, 0, sizeof(num_cnt));
        for (int j = 1; j <= cnum; j++) num_cnt[A[i][j]]++;
        for (int j = 1; j < MAX; j++) {
          if (num_cnt[j] == 0) continue;
          v.push_back({num_cnt[j], j});
        }
        sort(v.begin(), v.end());

        for (int j = 1; j <= cnum; j++) A[i][j] = 0;
        for (int j = 0; j < v.size(); j++) {
          A[i][++idx] = v[j].second;
          A[i][++idx] = v[j].first;
        }
        rcnum.push_back(idx);
      }
      sort(rcnum.begin(), rcnum.end());
      cnum = rcnum.back();
    }
    else {
      for (int i = 1; i <= cnum; i++) {
        vector<pair<int, int>> v;
        int idx = 0;

        memset(num_cnt, 0, sizeof(num_cnt));
        for (int j = 1; j <= rnum; j++) num_cnt[A[j][i]]++;
        for (int j = 1; j < MAX; j++) {
          if (num_cnt[j] == 0) continue;
          v.push_back({num_cnt[j], j});
        }
        sort(v.begin(), v.end());

        for (int j = 1; j <= rnum; j++) A[j][i] = 0;
        for (int j = 0; j < v.size(); j++) {
          A[++idx][i] = v[j].second;
          A[++idx][i] = v[j].first;
        }
        rcnum.push_back(idx);
      }
      sort(rcnum.begin(), rcnum.end());
      rnum = rcnum.back();
    }
  }
  if (flag) cout << ans;
  else cout << -1;
  return 0;
}