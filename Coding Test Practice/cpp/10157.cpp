#include <iostream>
using namespace std;

int C, R, K;
int x, y;

void findXY() {
    int bound = 2*C + 2*R - 4;
    if (K > bound) {
        C -= 2; R -= 2; K -= bound;
        x += 1; y += 1;
        findXY();
    }
    else {
        if (K<=R){
            y += (K-1);
            return;
        }
        else if (R<K && K<=(R+C-1)) {
            y += (R-1);
            x += (K-R);
            return;
        }
        else if ((R+C-1)<K && K<=(2*R+C-2)) {
            x += (C-1);
            y += (R-1) - (K - (R + C - 1));
            return;
        }
        else {
            x += (C-1) - (K - (2*R + C -2));
            return;
        }
    }
}

int main() {
    cin>>C>>R>>K;
    int max = C*R;
    x = 1; y = 1;
    if (K > max) {
        cout<<"0"<<endl;
    }
    else {
        findXY();
        cout<<x<<" "<<y<<endl;
    }
    return 0;
}