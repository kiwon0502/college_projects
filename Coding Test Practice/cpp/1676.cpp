#include <iostream>
#define MAX 500;
using namespace std;
int N;

int findfactor(int div) {
    int num = 0;
    for (int i = div; i<=N; i *= div) {
        num += int(N/i);
    }
    return num;
}

int main() {
    cin>>N;
    int two = findfactor(2);
    int five = findfactor(5);
    two > five ? (cout<<five<<endl) : (cout<<two<<endl);
    return 0;
}