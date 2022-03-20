// #include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#define pp pair<int, int>
using namespace std;

int N;
vector<pp> v;
int ans[1000000];

bool cmp(pp a, pp b) {
    if (a.second == b.second) return a.first < b.first;
    return a.second < b.second;
}

int main() {
    // ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        int temp; scanf("%d", &temp);
        v.push_back({i, temp});
    }
    sort(v.begin(), v.end(), cmp);

    // 첫 번째 시도
    // for (int i = 0; i < v.size(); i++) {
    //     int cnt = 0;
    //     for (int j = i - 1; j >= 0; j--) {
    //         if (v[i].second != v[j].second) {
    //             int temp = 0;
    //             for (int k = j - 1; k >= 0; k--) {
    //                 if (v[j].second != v[k].second) {
    //                     temp = k + 1;
    //                     break;
    //                 }
    //             }
    //             cnt = temp + 1;
    //         }
    //     }
    //     ans[v[i].first] = cnt;
    // }

    // 시간 초과
    // for (int i = 0; i < v.size(); i++) {
    //     int cnt = 0;
    //     for (int j = i - 1; j >= 0; j--) {
    //         if (v[i].second == v[j].second) continue;
    //         else {
    //             cnt = ans[v[j].first] + 1;
    //             break;
    //         }
    //     }
    //     ans[v[i].first] = cnt;
    // }

    for (int i = 0; i < v.size(); i++) {
        int cnt = 0;
        for (int j = i - 1; j >= 0; j--) {
            if (v[i].second == v[j].second) {
                cnt = ans[v[j].first];
                break;
            }
            else {
                cnt = ans[v[j].first] + 1;
                break;
            }
        }
        ans[v[i].first] = cnt;
    }


    for (int i = 0; i < N; i++) {
        printf("%d ", ans[i]);
    }
    return 0;
}