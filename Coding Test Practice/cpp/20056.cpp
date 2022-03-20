#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#define ll long long int
using namespace std;

typedef struct _fireball {
    ll m;
    ll s;
    ll d;
    bool even = true;
    bool flag = true;
    int n = 0;
} fireball;

ll N, M, K;
fireball arr[51][51];
fireball after[51][51];

void chg() {
    for (ll i=1; i<=N; i++) {
        for (ll j=1; j<=N; j++) {
            arr[i][j] = after[i][j];
        }
    }
}

void init() {
    fireball initial = {0, 0, 0};
    for (ll i=1; i<=N; i++) {
        for (ll j=1; j<=N; j++) {
            after[i][j] = initial;
        }
    }
}

void a1() {
    for (ll i=1; i<=N; i++) {
        for (ll j=1; j<=N; j++) {
            ll row, col;
            switch(arr[i][j].d) {
                case 0:
                    row = i - arr[i][j].s;
                    if (row <= 0) {
                        row += N;
                    }
                    after[row][j].m += arr[i][j].m;
                    after[row][j].s += arr[i][j].s;
                    if (after[row][j].even != arr[i][j].even) after[row][j].flag = true;
                    after[row][j].n++;
                    break;
                case 1:
                    row = i - arr[i][j].s;
                    col = i + arr[i][j].s;
                    if (row <= 0) {
                        row += N;
                    }
                    if (col >= N) {
                        col -= N;
                    }
                    after[row][col].m += arr[i][j].m;
                    after[row][col].s += arr[i][j].s;
                    if (after[row][col].even != arr[i][j].even) after[row][col].flag = true;
                    after[row][col].n++;
                    break;
                case 2:
                    col = i + arr[i][j].s;
                    if (col >= N) {
                        col -= N;
                    }
                    after[i][col].m += arr[i][j].m;
                    after[i][col].s += arr[i][j].s;
                    if (after[i][col].even != arr[i][j].even) after[i][col].flag = true;
                    after[i][col].n++;
                    break;
                case 3:
                    row = i + arr[i][j].s;
                    col = i + arr[i][j].s;
                    if (row >= N) {
                        row -= N;
                    }
                    if (col >= N) {
                        col -= N;
                    }
                    after[row][col].m += arr[i][j].m;
                    after[row][col].s += arr[i][j].s;
                    if (after[row][col].even != arr[i][j].even) after[row][col].flag = true;
                    after[row][col].n++;
                    break;
                case 4:
                    row = i + arr[i][j].s;
                    if (row >= N) {
                        row -= N;
                    }
                    after[row][j].m += arr[i][j].m;
                    after[row][j].s += arr[i][j].s;
                    if (after[row][j].even != arr[i][j].even) after[row][j].flag = true;
                    after[row][j].n++;
                    break;
                case 5:
                    row = i + arr[i][j].s;
                    col = i - arr[i][j].s;
                    if (row >= N) {
                        row -= N;
                    }
                    if (col <= 0) {
                        col += N;
                    }
                    after[row][col].m += arr[i][j].m;
                    after[row][col].s += arr[i][j].s;
                    if (after[row][col].even != arr[i][j].even) after[row][col].flag = true;
                    after[row][col].n++;
                    break;
                case 6:
                    col = i - arr[i][j].s;
                    if (col <= 0) {
                        col += N;
                    }
                    after[i][col].m += arr[i][j].m;
                    after[i][col].s += arr[i][j].s;
                    if (after[i][col].even != arr[i][j].even) after[i][col].flag = true;
                    after[i][col].n++;
                    break;
                case 7:
                    row = i - arr[i][j].s;
                    col = i - arr[i][j].s;
                    if (row <= 0) {
                        row += N;
                    }
                    if (col <= 0) {
                        col += N;
                    }
                    after[row][col].m += arr[i][j].m;
                    after[row][col].s += arr[i][j].s;
                    if (after[row][col].even != arr[i][j].even) after[row][col].flag = true;
                    after[row][col].n++;
                    break;
                default:
                    break;
            }
        }
    }
}

void a2() {
    for (ll i=1; i<=N; i++) {
        for (ll j=1; j<=N; j++) {
            if (after[i][j].m/5) after[i][j] = {0,0,0};
            
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>N>>M>>K;

    for (ll i=1; i<=M; i++) {
        ll r, c, m, s, d;
        cin>>r>>c>>m>>s>>d;
        fireball crash = {m, s, d, !(m%2)};
        arr[r][c] = crash;
    }

    for (ll i=1; i<=K; i++) {
        init();
        a1();
        chg();
    }

    return 0;
}