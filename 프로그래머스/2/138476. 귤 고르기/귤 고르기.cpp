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
    vector<pair<int,int>> v; // (1,1) (2,2) 과일크기 - 개수
    for(auto m : um){
        v.push_back({m.first, m.second});
    }
    
    sort(v.begin(), v.end(), cmp);
    
    int answer = 0;
    
    for(auto a : v){
        if(k <= 0) break; // 성능 향상
        if(k > 0){
            k -= a.second;
            answer++;
        }
    }
    return answer;
}