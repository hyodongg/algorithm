#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> board;

int zero_cnt;
int one_cnt;

// 압축할 수 있는지
bool canCompress(int r, int c, int size){
    int num = board[r][c];
    for(int i = r; i < r + size; i++){
        for(int j = c; j < c + size; j++){
            if(num != board[i][j]) return false;
        }
    }
    return true;
}

void dfs(int r, int c, int size){
    // 압축할 수 있는 경우 size가 1일때도 되므로 통일 됨
    if(canCompress(r, c, size)){
        // 숫자에 맞게 더하기
        if(board[r][c] == 0) zero_cnt += 1;
        if(board[r][c] == 1) one_cnt += 1;
        return;
    }
    
    // 다음 나눠질 정사각형의 크기
    int ns = size / 2;
    
    dfs(r, c, ns); // 왼쪽 위 사각형
    dfs(r + ns, c, ns); // 왼쪽 아래 사각형
    dfs(r, c + ns, ns); // 오른쪽 위 사각형
    dfs(r + ns, c + ns, ns); // 오른쪽 아래 사각형
    
}

vector<int> solution(vector<vector<int>> arr) {
    board = arr;
    zero_cnt = 0;
    one_cnt = 0;
    
    int size = board.size();
    
    // 왼쪽 위 꼭짓점을 넣는다.
    dfs(0, 0, size);
    
    return vector<int>{zero_cnt, one_cnt};
}