#include <string>
#include <vector>
#include <bits/stdc++.h>

// 시간 복잡도 계산
// 행,열 최댓값은 100
// 쿼리 개수는 10000개. 총 최대 1만번 회전
// 회전 한 번 할때 한 변 4xO(n) 즉 최대 4만번 
// 시간초과는 ㄴㄴ..?

using namespace std;

vector<vector<int>> board;
int N;
int M;

// 시계방향으로 회전하고 제일 작은 수찾기
// 시계는 i,j -> j, n - 1 - i

void debug(){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }    
    cout << "==============" << "\n";
}

int rotate(int r1, int c1, int r2, int c2){ //(1,1) (4,3)일 때
    int temp = board[r1][c1]; // 8을 저장 
    int mn = temp; // 어차피 움직일 수니까 최솟값에 저장
    
    // 맨 왼쪽 줄
    for(int i = r1; i <= r2 - 1; i++){
        board[i][c1] = board[i + 1][c1];
        // 움직여지는 값으로 최솟값 갱신
        mn = min(mn, board[i + 1][c1]);
    }
    // 맨 아래 줄 <-
    for(int j = c1; j <= c2 - 1; j++){
        board[r2][j] = board[r2][j + 1];
        mn = min(mn, board[r2][j + 1]);
    }
    // 맨 오른쪽 줄
    for(int i = r2; i >= r1 + 1; i--){
        board[i][c2] = board[i - 1][c2];
        mn = min(mn, board[i - 1][c2]);
    }
    // 맨 윗 줄 ->
    for(int j = c2; j >= c1 + 1; j--){
        board[r1][j] = board[r1][j - 1];
        mn = min(mn, board[r1][j - 1]);
    }
    
    // 밀려서 없어진 수 넣어주기
    board[r1][c1+1] = temp;
    
    return mn;
}


vector<int> solution(int rows, int columns, vector<vector<int>> queries) {
    board.assign(rows, vector<int>(columns, 0));
    N = board.size();
    M = board[0].size();
    int num = 1;
    // board 형성하기.
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            board[i][j] = num;
            num++;
        }
    }
    
    vector<int> answer;
    
    for(int i = 0; i < queries.size(); i++){
        vector<int> query = queries[i];
        // 회전할 때마다 정답에 추가
        // 0-based로 바꾸기 위해 1씩 뺌
        answer.push_back(rotate(query[0] - 1, query[1] - 1, query[2] - 1, query[3] - 1));
    }
    
    return answer;
}