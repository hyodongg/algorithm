#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

int result;

void dfs(int sum, int num, int n){
    // cout << "dfs " << sum << " " << num << " " << n << " ";
    if(sum == n) {result++; return;}
    if(sum > n) return;
    
    num += 1;
    sum += num;
    dfs(sum, num, n);
    
}

int solution(int n) {
    result = 0;
    for(int i = 1; i <= n; i++){
        dfs(i, i, n);
    }
    
    return result;
}
 