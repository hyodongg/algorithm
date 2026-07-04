#include <vector>
#include <bits/stdc++.h>

using namespace std;

int solution(int n) {
    // dp[i]는 가로 i를 채우는 방법의 수
    vector<int> dp(n + 1);
    
    dp[1] = 1; 
    dp[2] = 2; 
    // 세로로 1개 배치 -> 마지막에 세로로 타일 1개를 세우면, 남은 가로 길이는 i-1
    // 가로로 2개 배치 -> 마지막에 가로로 타일 2개를 쌓으면, 남은 가로 길이는 i-2
    for(int i = 3; i <= n; i++){
        dp[i] = (dp[i-1] + dp[i-2]) % 1000000007;
    }
    
    return dp[n];
}