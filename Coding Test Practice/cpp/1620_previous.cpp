#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;
#define MAX 100000

int N, M;

bool is_digit(string s) {
    return atoi(s.c_str()) != 0 || s.compare("0") == 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    cin>>N>>M;
    string* pokemon = new string[N];

    for (int i=0; i<N; i++) {
        cin>>pokemon[i];
    }

    string question;
    for (int i=0; i<M; i++) {
        cin>>question;
        if (is_digit(question.substr(0, 1))) {
            cout<<pokemon[stoi(question) - 1]<<"\n";
        }
        else {
            for (int j=0; i<N; j++) {
                if (question == pokemon[j]) {
                    cout<<(j + 1)<<"\n";
                    break;
                }
            }
        }
    }
    return 0;
}