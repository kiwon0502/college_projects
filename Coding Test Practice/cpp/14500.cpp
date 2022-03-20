#include <iostream>
#include <algorithm>
#include <vector>
#define ll long long int
using namespace std;

ll N, M;
ll arr[501][501];
vector<ll> sum;

void a1() {
    for (ll i=1; i<=N-3; i++) {
        for (ll j=1; j<=M; j++) {
            sum.push_back(arr[i][j] + arr[i+1][j] + arr[i+2][j] + arr[i+3][j]);
        }
    }
    for (ll i=1; i<=N; i++) {
        for (ll j=1; j<=M-3; j++) {
            sum.push_back(arr[i][j] + arr[i][j+1] + arr[i][j+2] + arr[i][j+3]);
        }
    }
}

void a2() {
    for (ll i=1; i<=N-1; i++) {
        for (ll j=1; j<=M-1; j++) {
            sum.push_back(arr[i][j] + arr[i][j+1] + arr[i+1][j] + arr[i+1][j+1]);
        }
    }
}

void a3() {
    for (ll i=1; i<=N-2; i++) {
        for (ll j=1; j<=M-1; j++) {
            sum.push_back(arr[i][j] + arr[i+1][j] + arr[i+2][j] + arr[i+2][j+1]);
        }
    }
    for (ll i=1; i<=N-2; i++) {
        for (ll j=2; j<=M; j++) {
            sum.push_back(arr[i][j] + arr[i+1][j] + arr[i+2][j] + arr[i+2][j-1]);
        }
    }
    for (ll i=1; i<=N-1; i++) {
        for (ll j=1; j<=M-2; j++) {
            sum.push_back(arr[i][j] + arr[i+1][j] + arr[i][j+1] + arr[i][j+2]);
        }
    }
    for (ll i=1; i<=N-1; i++) {
        for (ll j=3; j<=M; j++) {
            sum.push_back(arr[i][j] + arr[i+1][j] + arr[i][j-1] + arr[i][j-2]);
        }
    }
    for (ll i=1; i<=N-2; i++) {
        for (ll j=1; j<=M-1; j++) {
            sum.push_back(arr[i][j] + arr[i][j+1] + arr[i+1][j+1] + arr[i+2][j+1]);
        }
    }
    for (ll i=1; i<=N-2; i++) {
        for (ll j=2; j<=M; j++) {
            sum.push_back(arr[i][j] + arr[i][j-1] + arr[i+1][j-1] + arr[i+2][j-1]);
        }
    }
    for (ll i=1; i<=N-1; i++) {
        for (ll j=3; j<=M; j++) {
            sum.push_back(arr[i][j] + arr[i+1][j] + arr[i+1][j-1] + arr[i+1][j-2]);
        }
    }
    for (ll i=1; i<=N-1; i++) {
        for (ll j=1; j<=M-2; j++) {
            sum.push_back(arr[i][j] + arr[i+1][j] + arr[i+1][j+1] + arr[i+1][j+2]);
        }
    }
}

void a4() {
    for (ll i=1; i<=N-2; i++) {
        for (ll j=1; j<=M-1; j++) {
            sum.push_back(arr[i][j] + arr[i+1][j] + arr[i+1][j+1] + arr[i+2][j+1]);
        }
    }
    for (ll i=1; i<=N-2; i++) {
        for (ll j=2; j<=M; j++) {
            sum.push_back(arr[i][j] + arr[i+1][j] + arr[i+1][j-1] + arr[i+2][j-1]);
        }
    }
    for (ll i=1; i<=N-1; i++) {
        for (ll j=1; j<=M-2; j++) {
            sum.push_back(arr[i][j] + arr[i][j+1] + arr[i+1][j+1] + arr[i+1][j+2]);
        }
    }
    for (ll i=1; i<=N-1; i++) {
        for (ll j=3; j<=M; j++) {
            sum.push_back(arr[i][j] + arr[i][j-1] + arr[i+1][j-1] + arr[i+1][j-2]);
        }
    }
}

void a5() {
    for (ll i=1; i<=N-1; i++) {
        for (ll j=1; j<=M-2; j++) {
            sum.push_back(arr[i][j] + arr[i][j+1] + arr[i][j+2] + arr[i+1][j+1]);
        }
    }
    for (ll i=2; i<=N; i++) {
        for (ll j=1; j<=M-2; j++) {
            sum.push_back(arr[i][j] + arr[i][j+1] + arr[i][j+2] + arr[i-1][j+1]);
        }
    }
    for (ll i=1; i<=N-2; i++) {
        for (ll j=1; j<=M-1; j++) {
            sum.push_back(arr[i][j] + arr[i+1][j] + arr[i+1][j+1] + arr[i+2][j]);
        }
    }
    for (ll i=1; i<=N-2; i++) {
        for (ll j=2; j<=M; j++) {
            sum.push_back(arr[i][j] + arr[i+1][j] + arr[i+1][j-1] + arr[i+2][j]);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>N>>M;
    for (ll i=1; i<=N; i++) {
        for (ll j=1; j<=M; j++) {
            cin>>arr[i][j];
        }
    }
    a1();
    a2();
    a3();
    a4();
    a5();
    sort(sum.begin(), sum.end());
    cout<<sum[sum.size()-1];
    return 0;
}