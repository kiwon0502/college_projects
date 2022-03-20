#include <iostream>
#include <vector>
#include <queue>
#define MAX 100005
using namespace std;

int N;
priority_queue<int> MaxQ;                                       // MID보다 작은 값들을 Maxheap에 저장
priority_queue<int, vector<int>, greater<int>> MinQ;            // MIND보다 큰 값들을 Minheap에 저장

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>N;
    while (N--) {
        int x; cin>>x;
        if (MinQ.size() == MaxQ.size()) {
            MaxQ.push(x);
        }
        else MinQ.push(x);

        if (!MinQ.empty() && !MaxQ.empty() && MinQ.top() < MaxQ.top()) {
            int min_value = MinQ.top();
            MinQ.pop();
            int max_value = MaxQ.top();
            MaxQ.pop();

            MaxQ.push(min_value);
            MinQ.push(max_value);
        }
        cout<<MaxQ.top()<<"\n";
    }
    return 0;
}