#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int N, M;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>N>>M;

    vector<string> hear(N);
    vector<string> ans;
    int num = 0;

    for (int i=0; i<N; i++) {
        cin>>hear[i];
    }

    sort(hear.begin(), hear.end());

    for (int i=1; i<=M; i++) {
        string s;
        cin>>s;

        int low = 0, high = N-1;
        while (low <= high) {
            int mid = (low + high) / 2;
            if (hear[mid] == s) {
                ans.push_back(s);
                num++;
                break;
            }
            else if (hear[mid] < s) {
                low = mid + 1;
            }
            else {
                high = mid - 1;
            }
        }
    }

    sort(ans.begin(), ans.end());
    cout<<num<<"\n";
    for (int i=0; i<num; i++) {
        cout<<ans[i]<<"\n";
    }

    return 0;
}