#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;
vector<vector<char>> Maps;
int N;
int M;
vector<vector<bool>> visited;

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

void debug(){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            cout << Maps[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "===============" << "\n";
}

// 범위 체크
bool isRange(int r, int c){
    if(r < 0 || r >= N || c < 0 || c >= M) return false;
    return true;
}

int bfs(int r, int c){
    int sum = 0;
    queue<pair<int,int>> q;
    visited[r][c] = true;
    q.push({r,c});
    sum += Maps[r][c] - '0';
    
    while(!q.empty()){
        auto [cur_r, cur_c] = q.front();
        q.pop();
        
        for(int d = 0; d < 4; d++){
            int nr = cur_r + dr[d];
            int nc = cur_c + dc[d];
            
            // 범위 벗어나는 경우
            if(!isRange(nr,nc)) continue;
            
            // 방문X && 벽X
            if(!visited[nr][nc] && Maps[nr][nc] != 'X'){
                sum += Maps[nr][nc] - '0';
                visited[nr][nc] = true;
                q.push({nr,nc});
            }
        }
    }
    return sum;
}

vector<int> solution(vector<string> maps){
    N = maps.size();
    M = maps[0].size();
    Maps.assign(N, vector<char>(M, 'X'));
    visited.assign(N, vector<bool>(M, false));
    
    // Maps 형성
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            char c = maps[i][j];
            if(isdigit(c)) Maps[i][j] = c;
        }
    }
    
    //debug();
    
    vector<int> answer;
    
    
    
    // 벽이 아니고 방문하지 않았다면 bfs시작
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            if(!visited[i][j] && Maps[i][j] != 'X'){
                answer.push_back(bfs(i,j));
            }
        }
    }
    
    if(answer.empty()) return vector<int>{-1};
    
    sort(answer.begin(), answer.end());
    
    
    return answer;
}