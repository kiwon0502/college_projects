#include <iostream>
#include <algorithm>
using namespace std;

int N;
int Max[3], Min[3];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>N;
    cin>>Max[0]>>Max[1]>>Max[2];
    for (int i = 0; i < 3; i++) Min[i] = Max[i];

    int input[6];
    for (int i = 1; i < N; i++) {
        for (int j = 0; j < 3; j++) cin>>input[j];
        for (int j = 3; j < 6; j++) input[j] = input[j - 3];

        input[0] += max(Max[0], Max[1]);
        input[1] += max({Max[0], Max[1], Max[2]});
        input[2] += max(Max[1], Max[2]);
        for (int j = 0; j < 3; j++) Max[j] = input[j];

        input[3] += min(Min[0], Min[1]);
        input[4] += min({Min[0], Min[1], Min[2]});
        input[5] += min(Min[1], Min[2]);
        for (int j = 0; j < 3; j++) Min[j] = input[j + 3];
    }

    cout<<max({Max[0], Max[1], Max[2]})<<" "<<min({Min[0], Min[1], Min[2]});
    return 0;
}