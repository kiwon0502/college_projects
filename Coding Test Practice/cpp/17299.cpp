#include <iostream>
#include <stack>
#include <algorithm>
using namespace std;

int arr[1000001];
int freq[1000001];
int ans[1000001];
stack<int> s;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int N; cin>>N;
    for (int i = 0; i < N; i++) {
        cin>>arr[i];
        freq[arr[i]]++;
    }

    for (int i = N - 1; i >= 0; i--) {
        while (!s.empty() && freq[arr[i]] >= freq[s.top()]) {
            s.pop();
        }
        ans[i] = s.empty() ? -1 : s.top();
        s.push({arr[i]});
    }

    for (int i = 0; i < N; i++) cout<<ans[i]<<" ";
    return 0;
}