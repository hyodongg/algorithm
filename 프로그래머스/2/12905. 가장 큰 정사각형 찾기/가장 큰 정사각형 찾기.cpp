#include <iostream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

int solution(vector<vector<int>> board)
{
    int n = board.size();
    int m = board[0].size();
    int mx = 0;
    
    vector<vector<int>> dp(n, vector<int>(m,0));
    for(int i = 0; i < n; i++){ // 0열 채우기
        dp[i][0] = board[i][0];
        mx = max(mx, dp[i][0]); // mx 초기값
    }
    for(int j = 0; j < m; j++){
        dp[0][j] = board[0][j];
        mx = max(mx, dp[0][j]);
    }
    // 초기값 설정
    for(int i = 1; i < n; i++){
        for(int j = 1; j < m; j++){
            if(board[i][j] == 1){
                dp[i][j] = min({dp[i-1][j],dp[i-1][j-1],dp[i][j-1]}) + board[i][j];
            }
            else{
                dp[i][j] = 0;
            }
        }
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            mx = max(mx,dp[i][j]);
        }
    }
    
    return mx*mx;
}