#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

int solution(int x, int y, int n) {
    if(x == y) return 0;
    
    queue<pair<int,int>> q;
    vector<bool> visited(1000001,false);
    
    q.push({x,0});
    visited[x] = true;
    
    while(!q.empty()){
        auto [cur, cnt] = q.front();
        q.pop();
        
        int next_nums[3] = {cur + n, cur * 2, cur * 3};
        
        for(int next_num : next_nums){
            if(next_num == y) return cnt + 1;
            
            if(next_num < y && !visited[next_num]){
                q.push({next_num, cnt + 1});
                visited[next_num] = true;
            }
        }
    }
    
    return -1;
}