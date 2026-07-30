#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

int solution(vector<vector<int>> board)
{
    int n = board.size();
    int m = board[0].size();
    
    // dp[i][j] = i,j를 우하단 꼭짓점으로 하는 가장 큰 정사각형의 한 변
    vector<vector<int>> dp(n, vector<int>(m, 0));
    
    int mx = 0;
    
    for(int i = 0; i < n; i++){
        dp[i][0] = board[i][0];
        mx = max(mx, dp[i][0]);
    }
    
    for(int j = 0;  j< m; j++){
        dp[0][j] = board[0][j];
        mx = max(mx, dp[0][j]);
    }
    
    
    
    for(int i = 1; i < n; i++){
        for(int j = 1; j < m; j++){
            if(board[i][j] == 0) dp[i][j] = 0;
            else{
                dp[i][j] = min({dp[i-1][j], dp[i-1][j-1], dp[i][j-1]}) + 1;
            }
        }
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            mx = max(mx, dp[i][j]);
        }
    }
    
    return mx*mx;
}