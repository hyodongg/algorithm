#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<int> t(n + 1); // 걸리는 시간
    vector<int> p(n + 1); // 외주 보상
    
    
    for(int i = 1; i <= n; i++){
        cin >> t[i] >> p[i];
    }
    // t[i] = {2,2,1};
    // p[i] = {10,26,15};

    vector<int> dp(n + 1);
    dp[0] = 0;

    for(int i = 1; i <= n; i++){
        dp[i] = dp[i - 1];

        for(int j = 1; j <= n; j++){
            if(j + t[j] - 1 == i){
                dp[i] = max(dp[i], dp[j - 1] + p[j]);
            }
        }
    }

    cout << dp[n] << "\n";

    return 0;
}
