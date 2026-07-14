#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

vector<int> solution(int n) {
    int dr[3] = {1, 0, -1}; // 아래, 오른쪽, 대각선 위
    int dc[3] = {0, 1, -1};
    int cur_r = 0, cur_c = 0;
    int dir = 0;
    vector<vector<int>> board(n, vector<int>(n, 0));
    int cur_num = 1;
    int cnt = n * (n + 1) / 2;
    
    while(cur_num <= cnt){
        board[cur_r][cur_c] = cur_num;
        
        int nr = cur_r + dr[dir];
        int nc = cur_c + dc[dir];
        
        if(nr >= n || nr < 0 || nc >= n || nc < 0 || board[nr][nc] != 0){
            dir = (dir + 1) % 3; // 방향 바꾸기
            nr = cur_r + dr[dir];
            nc = cur_c + dc[dir];
        }
        
        cur_r = nr;
        cur_c = nc;
        
        cur_num++;
    }
    
    vector<int> answer;
    
    for(const vector<int>& row : board){
        for(int col : row){
            if(col != 0){
                answer.push_back(col);
            }
        }
    }
    
    return answer;
}


// 1
// 2 9
// 3 10 8
// 4 5 6 7