#include <cstdio>
using namespace std;

int N, M, cand_size;
int recommend[101];
int when[101];

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < M; i++) {
        int rec; scanf("%d", &rec);
        // 이미 추천 받은 경우
        if (recommend[rec] > 0) recommend[rec]++;
        // 처음 추천 받은 경우
        else {
            // 아직 사진틀이 충분한 경우
            if (cand_size < N) {
                recommend[rec]++;
                when[rec] = i;
                cand_size++;
            }
            // 교체해야하는 경우
            else {
                int change, minR = 6974;
                for (int i = 1; i <= 100; i++) {                    
                    if (!recommend[i]) continue;    // 추천 수가 0

                    // 추천 수가 적은 경우 이걸 change
                    if (minR > recommend[i]) {
                        change = i;
                        minR = recommend[i];
                    }
                    // 동률인 경우 오래된 것 change
                    else if (minR == recommend[i]) {
                        if (when[i] < when[change]) change = i;
                    }
                }

                // change 과정
                recommend[rec]++;
                when[rec] = i;

                recommend[change] = 0;
                when[change] = 0;
            }
        }
    }

    for (int i = 1; i <= 100; i++) {
        if (recommend[i]) printf("%d ", i);
    }
    return 0;
}