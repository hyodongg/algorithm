#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

bool cmp(pair<int,int> p1, pair<int,int> p2){
    return p1.second > p2.second;
}

int solution(int k, vector<int> tangerine) {
    
    unordered_map<int,int> um;
    for(int t : tangerine){
        um[t] += 1;
    }
    vector<pair<int,int>> v(um.begin(), um.end());
    
    sort(v.begin(), v.end(), cmp);
    
    int answer = 0;
    
    for(auto [size, cnt] : v){
        k -= cnt;
        answer += 1;
        if(k <= 0) return answer;
    }
}