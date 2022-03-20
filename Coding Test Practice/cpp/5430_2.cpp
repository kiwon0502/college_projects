#include <iostream>
#include <string>
#include <cstring>
using namespace std;

int T, head, tail;
int X[100001];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>T;
    for (int t = 0; t < T; t++) {
        memset(X, 0, sizeof(X));
        string p; cin>>p;                       // 수행할 함수
        int size; cin>>size;                    // 배열 원소 개수
        head = 1; tail = size;
        bool reverse_flag = false, error_flag = false;

        string l; cin>>l;
        l = l.substr(1, l.length() - 2);
        if (l.length() != 0) {
            int previous = 0, current = 0, idx = 1;
            string substring;

            current= l.find(',');
            //find는 찾을게 없으면 npos를 리턴함
            while(current != string::npos){
                substring = l.substr(previous, current - previous);
                X[idx++] = stoi(substring);
                previous = current + 1;
                current = l.find(',', previous);
            }
            substring = l.substr(previous, current - previous);
            X[idx++] = stoi(substring);
        }

        for (int i = 0; i < p.length(); i++) {
            switch(p[i]) {
                case 'R':
                    reverse_flag = !reverse_flag;
                    break;
                case 'D':
                    if (size > 0) {
                        if (!reverse_flag) head++;
                        else tail--;
                        size--;
                    }
                    else error_flag = true;
                    break;
            }
            if (error_flag) break;
        }

        if (error_flag) {
            cout<<"error\n";
            continue;
        }
        else if (!size) {
            cout<<"[]\n";
            continue;
        }
        
        if (!reverse_flag) {
            cout<<"[";
            for (int i = head; i < tail; i++) {
                cout<<X[i]<<",";
            }
            cout<<X[tail]<<"]\n";
        }
        else {
            cout<<"[";
            for (int i = tail; i > head; i--) {
                cout<<X[i]<<",";
            }
            cout<<X[head]<<"]\n";
        }
    }
    return 0;
}
