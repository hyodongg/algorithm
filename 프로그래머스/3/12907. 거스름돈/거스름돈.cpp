#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

int solution(int n, vector<int> money) {
    vector<int> dp(n + 1,0); // dp[n] => n원을 만드는 경우의 수
    dp[0] = 1; // 0원은 아무것도 안 내면 되므로 1
    
    for(int i = 0; i < money.size(); i++){
        int won = money[i];
        
        for(int j = won; j <= n; j++){
            // j원을 만드는 방법은 기존 dp[j]에 현재 더할 won을 뺀 dp[j-won] 더하기
            dp[j] += dp[j - won]; 
            
            dp[j] %= 1000000007;
        }
    }
    return dp[n];
}