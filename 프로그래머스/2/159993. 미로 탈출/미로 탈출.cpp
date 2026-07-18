#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

int dr[4] = {1, -1, 0, 0};
int dc[4] = {0, 0, 1, -1};
vector<string> Maps;
int N;
int M;

int bfs(int start_r, int start_c, int end_r, int end_c){
    queue<pair<int,int>> q;
    vector<vector<int>> dist(N, vector<int>(M, -1));
    q.push({start_r, start_c});
    dist[start_r][start_c] = 0;
    while(!q.empty()){
        auto [cur_r, cur_c] = q.front();
        q.pop();
        
        for(int d = 0; d < 4; d++){
            int nr = cur_r + dr[d];
            int nc = cur_c + dc[d];
            
            // 넘어간 경우
            if(nr >= N || nr < 0 || nc >= M || nc < 0) continue;
            
            // 이미 방문한 경우
            if(dist[nr][nc] != -1) continue;
            
            // 벽으로 막힌 경우
            if(Maps[nr][nc] == 'X') continue;
            
            dist[nr][nc] = dist[cur_r][cur_c] + 1;
            q.push({nr,nc});
        }
    }
    
    return (dist[end_r][end_c] == -1) ? -1 : dist[end_r][end_c];
}

int solution(vector<string> maps) {
    Maps = maps;
    N = Maps.size();
    M = Maps[0].size();
    int start_r, start_c;
    int lever_r, lever_c;
    int exit_r, exit_c;
    
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            if(maps[i][j] == 'S'){
                start_r = i; start_c = j;
            }
            if(maps[i][j] == 'L'){
                lever_r = i; lever_c = j;
            }
            if(maps[i][j] == 'E'){
                exit_r = i; exit_c = j;
            }
        }
    }
    
    int stol = bfs(start_r, start_c, lever_r, lever_c);
    int ltoe = bfs(lever_r, lever_c, exit_r, exit_c);
    
    if(stol == -1 || ltoe == -1) return -1;
    
    return stol + ltoe;
    
    
}