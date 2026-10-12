#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> Dungeons;
int N;
vector<bool> visited;
int answer;

void dfs(int cur_tired, int cnt){
    // 종료조건
    if(cnt > answer) {
        answer = cnt;
    }
    
    for(int i = 0; i < N; i++){
        if(!visited[i] && cur_tired >= Dungeons[i][0]){
            visited[i] = true;
            dfs(cur_tired - Dungeons[i][1], cnt + 1);
            visited[i] = false;
        }
    }
    
}

// 최소필요도, 소모필요도
int solution(int k, vector<vector<int>> dungeons) {
    answer = 0;
    Dungeons = dungeons;
    N = Dungeons.size();
    visited.assign(N, false);
    dfs(k, 0);
    
    return answer;
}