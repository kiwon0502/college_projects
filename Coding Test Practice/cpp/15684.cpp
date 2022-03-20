#include <iostream>
using namespace std;

int N, M, H;
int map[35][15];

bool check() {
  for (int i = 1; i <= N; i++) {
    int r = 1, c = i;
    bool already = false; // 이미 꺾었다면 다시 못 꺾게하는 flag
    while (r <= H) {
      if (map[r][c] != 0 && !already) {
        c = map[r][c];
        already = true;
      }
      else {
        r++;
        already = false;
      }
    }
    if (c == i) continue;
    return false;
  }
  return true;
}

int main() {
  ios::sync_with_stdio(0); cout.tie(0); cin.tie(0);
  cin >> N >> M >> H;
  for (int i = 0; i < M; i++) {
    int a, b; cin >> a >> b;
    map[a][b] = b+1;
    map[a][b+1] = b;
  }

  // 0번 검사
  if (check()) {cout << 0; return 0;}

  // 1번 검사
  for (int i = 1; i <= H; i++) {
    for (int j = 1; j < N; j++) {
      if (map[i][j] == 0 && map[i][j+1] == 0) {
        map[i][j] = j+1;
        map[i][j+1] = j;
        if (check()) {cout << 1; return 0;}
        map[i][j] = map[i][j+1] = 0;
      }
    }
  }

  // 2번 검사
  for (int i = 1; i <= H; i++) {
    for (int j = 1; j < N; j++) {
      if (map[i][j] == 0 && map[i][j+1] == 0) {
        map[i][j] = j+1;
        map[i][j+1] = j;
        for (int ii = i; ii <= H; ii++) {
          for (int jj = 1; jj < N; jj++) {
            if (ii == i && jj <= j) continue;
            if (map[ii][jj] == 0 && map[ii][jj+1] == 0) {
              map[ii][jj] = jj+1;
              map[ii][jj+1] = jj;
              if (check()) {cout << 2; return 0;}
              map[ii][jj] = map[ii][jj+1] = 0;
            }
          }
        }
        map[i][j] = map[i][j+1] = 0;
      }
    }
  }

  // 3번 검사
  for (int i = 1; i <= H; i++) {
    for (int j = 1; j < N; j++) {
      if (map[i][j] == 0 && map[i][j+1] == 0) {
        map[i][j] = j+1;
        map[i][j+1] = j;
        for (int ii = i; ii <= H; ii++) {
          for (int jj = 1; jj < N; jj++) {
            if (ii == i && jj <= j) continue;
            if (map[ii][jj] == 0 && map[ii][jj+1] == 0) {
              map[ii][jj] = jj+1;
              map[ii][jj+1] = jj;
              for (int iii = ii; iii <= H; iii++) {
                for (int jjj = 1; jjj < N; jjj++) {
                  if (iii == ii && jjj <= jj) continue;
                  if (map[iii][jjj] == 0 && map[iii][jjj+1] == 0) {
                    map[iii][jjj] = jjj+1;
                    map[iii][jjj+1] = jjj;
                    if (check()) {cout << 3; return 0;}
                    map[iii][jjj] = map[iii][jjj+1] = 0;
                  }
                }
              }
              map[ii][jj] = map[ii][jj+1] = 0;
            }
          }
        }
        map[i][j] = map[i][j+1] = 0;
      }
    }
  }

  cout << -1;
  return 0;
}