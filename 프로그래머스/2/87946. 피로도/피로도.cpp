#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> Dungeons;
int mx;
vector<bool> visited;

// k는 현재 피로도, cnt는 현재 탐험한 던전의 개수
void backtrack(int k, int cnt){
    if(mx < cnt){
        mx = cnt;
    }
    
    
    for(int i = 0; i < Dungeons.size(); i++){
        // 최소 피로도 조건 만족하고, 아직 방문 안했다면
        if(k >= Dungeons[i][0] && !visited[i]){
            visited[i] = true;
            backtrack(k - Dungeons[i][1], cnt + 1);
            visited[i] = false;  
        }
    }
}

// 최소피로도 - 소모 피로도
int solution(int k, vector<vector<int>> dungeons) {
    Dungeons = dungeons;
    visited.assign(Dungeons.size(), false);
    mx = 0;
    backtrack(k, 0);
    return mx;
}