#include <string>
#include <vector>
using namespace std;

int solution(vector<vector<int>> board, vector<vector<int>> skill) {
    int N = board.size();
    int M = board[0].size();
    int W = M + 1;
    int H = N + 1;

    // 2차원 대신 1차원 벡터 하나로: temp[r][c] -> temp[r * W + c]
    vector<int> temp(H * W, 0);

    for (int i = 0; i < skill.size(); i++) {
        int type = skill[i][0];
        int r1 = skill[i][1], c1 = skill[i][2];
        int r2 = skill[i][3], c2 = skill[i][4];
        int val = (type == 2) ? skill[i][5] : -skill[i][5];

        temp[r1 * W + c1]             += val;
        temp[r1 * W + (c2 + 1)]       -= val;
        temp[(r2 + 1) * W + c1]       -= val;
        temp[(r2 + 1) * W + (c2 + 1)] += val;
    }

    // 가로 방향 누적합 (같은 행 안에서 연속 접근)
    for (int i = 0; i < H; i++) {
        for (int j = 1; j < W; j++) {
            temp[i * W + j] += temp[i * W + (j - 1)];
        }
    }

    // 세로 방향 누적합 (바깥=행, 안쪽=열 순서 유지 -> 연속 접근)
    for (int i = 1; i < H; i++) {
        for (int j = 0; j < W; j++) {
            temp[i * W + j] += temp[(i - 1) * W + j];
        }
    }

    int answer = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (board[i][j] + temp[i * W + j] > 0) answer++;
        }
    }

    return answer;
}