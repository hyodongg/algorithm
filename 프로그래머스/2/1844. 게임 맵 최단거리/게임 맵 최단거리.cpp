#include<vector>
#include <bits/stdc++.h>

// visted와 dist 따로 두는 풀이
using namespace std;

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

vector<vector<int>> Maps;
int N,M;

bool isRange(int r, int c){
    if(r < 0 || r >= N || c < 0 || c >= M) return false;
    return true;
}

int solution(vector<vector<int> > maps)
{
    Maps = maps;
    N = Maps.size();
    M = Maps[0].size();
    
    vector<vector<bool>> visited(N, vector<bool>(M, false));
    vector<vector<int>> dist(N, vector<int>(M, -1));
    
    
    queue<pair<int,int>> q;
    q.push({0,0});
    visited[0][0] = true;
    dist[0][0] = 1;
    
    while(!q.empty()){
        auto [cur_r, cur_c] = q.front();
        q.pop();
        
        for(int d = 0; d < 4; d++){
            int nr = cur_r + dr[d];
            int nc = cur_c + dc[d];
            
            // 격자 범위 벗어난 경우
            if(!isRange(nr,nc)) continue;
            
            // 이미 방문한 경우
            if(visited[nr][nc]) continue;
            
            // 벽인 경우
            if(Maps[nr][nc] == 0) continue;
            
            q.push({nr,nc});
            visited[nr][nc] = true;
            dist[nr][nc] = dist[cur_r][cur_c] + 1;
        
        }
    }
    
    
    if(dist[N-1][M-1] == -1) return -1;
    else return dist[N-1][M-1];
    
}