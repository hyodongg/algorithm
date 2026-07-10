#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> board;
int zero;
int one;

bool canQuard(int row, int col, int size){ // 격자판 숫자가 다 같은지
    int num = board[row][col];
    for(int i = row; i < row + size; i++){
        for(int j = col; j < col + size; j++){
            if(num != board[i][j]) return false;
        }
    }
    return true;
    
}

void dfs(int row, int col, int size){
    if(canQuard(row, col, size)){
        if(board[row][col] == 0) zero++;
        else one++;
        return;
    }
    int half = size / 2;
    dfs(row, col, half);
    dfs(row + half, col, half);
    dfs(row, col + half, half);
    dfs(row + half, col + half, half);
}

vector<int> solution(vector<vector<int>> arr) {
    board = arr;
    dfs(0,0, board.size());
    vector<int> answer{zero, one};
    
    return answer;
}