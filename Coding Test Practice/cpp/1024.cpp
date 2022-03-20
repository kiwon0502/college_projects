#include <iostream>
using namespace std;

int N, L;
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>N>>L;

    for (int i=L; i<=100; i++) {
        int a = (i * (i-1))/2;
        if ((N-a)%i == 0 && (N-a)/i >= 0) {
            int x = (N-a)/i;
            for (int j=0; j<i; j++) {
                cout<<(x+j)<<" ";
            }
            return 0;
        }
    }
    cout<<"-1"<<endl;
    return 0;
}