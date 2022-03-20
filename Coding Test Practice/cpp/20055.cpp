#include <iostream>
#include <algorithm>
#include <vector>
#define ll long long int
using namespace std;

ll N, K, ans, fin;
ll A[201];
bool robot[101];

void showinfo() {
    cout<<"======================="<<endl;
    for (ll i = 1; i <= N; i++) {
        cout<<A[i]<<" ";
    }
    cout<<endl;
    for (ll i = N+1; i <= 2*N; i++) {
        cout<<A[i]<<" ";
    }
    cout<<endl;
    for (ll i=1; i<=N; i++) {
        cout<<robot[i]<<" ";
    }
    cout<<endl;
}

void a1() {
    ll temp = A[2 * N];
    for (ll i = (2 * N - 1); i >= 1; i--) {
        A[i + 1] = A[i];
    }
    A[1] = temp;

    for (ll i = (N - 1); i >= 1; i--) {
        robot[i + 1] = robot[i];
    }
    robot[1] = false;
    if (robot[N]) robot[N] = false;
}

void a2() {
    for (ll i = (N-1); i >= 1; i--) {
        if (robot[i] && !robot[i+1] && A[i+1] > 0) {
            robot[i+1] = true;
            if((--A[i+1]) == 0) fin++;
            robot[i] = false;
        }
    }
    if (robot[N]) robot[N] = false;
}

void a3() {
    if (!robot[1] && A[1] > 0) {
        robot[1] = true;
        if(--A[1] == 0) fin++;
    }
}

bool a4() {
    if (fin >= K) return true;
    return false;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>N>>K;
    for (ll i=1; i<=2*N; i++) {
        cin>>A[i];
    }
    while(1) {
        ans++;
        a1();
        a2();
        a3();
        if (a4()) break;
    }
    cout<<ans;
    return 0;
}