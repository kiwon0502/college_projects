#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int T; cin >> T;
    while (T--) {
        int m; cin >> m;
        int data, mid;
        priority_queue<int> max_pq;
        priority_queue<int, vector<int>, greater<int>> min_pq;
        vector<int> ans;

        cin >> data;
        mid = data;
        ans.push_back(mid);
        for (int i = 2; i <= m; i++) {
            cin >> data;
            if (data < mid) max_pq.push(data);
            else min_pq.push(data);

            if (i%2 == 1) {
                int max_pq_size = max_pq.size();
                int min_pq_size = min_pq.size();
                
                if (max_pq_size < min_pq_size) {
                    max_pq.push(mid);
                    max_pq_size++;
                }
                else {
                    min_pq.push(mid);
                    min_pq_size++;
                }

                if (max_pq_size > min_pq_size) {
                    mid = max_pq.top();
                    max_pq.pop();
                }
                else {
                    mid = min_pq.top();
                    min_pq.pop();
                }
                ans.push_back(mid);
            }
        }

        int ss = ans.size();
        cout << ss << "\n";
        for (int i = 1; i <= ss; i++) {
            if (i != 1 && i%10 == 1) cout << "\n";
            cout << ans[i - 1] << " ";
        }
        cout << "\n";
    }

    return 0;
}
