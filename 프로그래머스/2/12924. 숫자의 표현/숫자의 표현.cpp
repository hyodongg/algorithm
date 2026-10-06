#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

bool dfs(int sum, int num, int n){
    // cout << "dfs " << sum << " " << num << " " << n << " ";
    if(sum == n) return true;
    if(sum > n) return false;
    
    num += 1;
    sum += num;
    return dfs(sum, num, n);
    
}

int solution(int n) {
    int result = 0;
    
    for(int i = 1; i <= n; i++){
        if(dfs(i, i, n)) result++;
    }
    
    return result;
}
 