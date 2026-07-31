#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

vector<vector<char>> Board;
vector<vector<int>> dist;
int n, m;

int dr[4] = {1, -1, 0, 0};
int dc[4] = {0, 0, -1, 1};

void debug(){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cout << Board[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "=============" << "\n";
}

int solution(vector<string> board) {
    n = board.size();
    m = board[0].size();
    Board.assign(n, vector<char>(m, '.'));
    dist.assign(n, vector<int>(m, -1));
    //debug();
    
    int start_r = 0;
    int start_c = 0;
    
    // 보드판 구성
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            Board[i][j] = board[i][j];
            if(Board[i][j] == 'R'){
                start_r = i;
                start_c = j;
            }
        }
    }
    
    //debug();
    
    int last_r = 0;
    int last_c = 0;
    queue<pair<int,int>> q;
    q.push({start_r, start_c});
    dist[start_r][start_c] = 0;
    
    while(!q.empty()){
        auto [cur_r, cur_c] = q.front();
        // 마지막 위치 저장
        last_r = cur_r;
        last_c = cur_c;
        q.pop();
        
        // 목표를 찾으면 조기 반환
        if(Board[cur_r][cur_c] == 'G'){
            return dist[cur_r][cur_c];
        }
        
        for(int d = 0; d < 4; d++){
            int nr = cur_r + dr[d];
            int nc = cur_c + dc[d];
            if(nr < 0 || nr >= n || nc < 0 || nc >= m || Board[nr][nc] =='D') continue;

            while(true){
                nr += dr[d];
                nc += dc[d];
                if(nr < 0 || nr >= n || nc < 0 || nc >= m || Board[nr][nc] == 'D') break;
            }
            nr -= dr[d];
            nc -= dc[d];
            if(dist[nr][nc] == -1){
                dist[nr][nc] = dist[cur_r][cur_c] + 1;
                q.push({nr,nc});
            }

        }
    }

    return -1;
}