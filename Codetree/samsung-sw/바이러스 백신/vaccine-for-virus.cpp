#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int N, M;
int hospital_cnt;
vector<vector<int>> board;
vector<pair<int,int>> hospitals; // 병원들의 좌표
vector<vector<pair<int,int>>> hospitalComb; // 병원들의 좌표 조합
vector<pair<int,int>> temp;
vector<vector<int>> dist;

int dr[4] = {1, -1, 0, 0};
int dc[4] = {0, 0, -1, 1};

void combHospital(int n, int r, int depth, int idx){
    if(depth == r){
        hospitalComb.push_back(temp);
        return;
    }
    for(int i = idx; i < hospitals.size(); i++){
        temp.push_back(hospitals[i]);
        combHospital(n, r, depth + 1, i + 1);
        temp.pop_back();
    }
}

// 병원 좌표들이 주어지고 각 병원좌표마다 bfs (0,0) (0,2) (2,4)
void bfs(int r, int c){
    queue<pair<int,int>> q;
    vector<vector<bool>> visited(N, vector<bool>(N, false));
    q.push({r,c});
    visited[r][c] = true;
    dist[r][c] = 0;

    while(!q.empty()){
        auto [cur_r, cur_c] = q.front();
        q.pop();

        for(int d = 0; d < 4; d++){
            int nr = cur_r + dr[d];
            int nc = cur_c + dc[d];

            // 넘으면 못 감
            if(nr < 0 || nr >= N || nc < 0 || nc >= N) continue;
            // 벽이면 못 감
            if(board[nr][nc] == 1) continue;

            if(!visited[nr][nc]){
                // dist가 더 작은 경우에만 업데이트
                if(dist[nr][nc] > dist[cur_r][cur_c] + 1){
                    dist[nr][nc] = dist[cur_r][cur_c] + 1;
                }
                visited[nr][nc] = true;
                q.push({nr, nc});
            }
        }
    }
}

void init(){
    dist.assign(N, vector<int>(N,9));
    hospital_cnt = 0;
    board.assign(N, vector<int>(N, 0));
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cin >> board[i][j];
            if(board[i][j] == 2) {
                hospital_cnt++;
                hospitals.push_back({i,j});
            }
        }
    }
}

void debug(){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cout << dist[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "================" << "\n";
}

void printComb(){
    for(int i = 0; i < hospitalComb.size(); i++){
        for(int j = 0; j < hospitalComb[i].size(); j++){
            cout << "(" << hospitalComb[i][j].first << "," << hospitalComb[i][j].second << ")";
        }
        cout << "\n";
    }
}

int getMin(){
    int time = 0;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(board[i][j] != 0) continue; // 바이러스 아닌 칸은 계산에서 제외
            if(dist[i][j] == 1000) return -1;
            time = max(time, dist[i][j]);
        }
    }

    return time;
}

int main() {
    cin >> N >> M;
    bool anySuccess = false;
    init();
    combHospital(hospital_cnt, M, 0, 0);
    //printComb();
    int min_time = 1e9;


    // 병원 조합 반복
    for(int i = 0; i < hospitalComb.size(); i++){
        vector<pair<int,int>> v = hospitalComb[i];
        dist.assign(N,vector<int>(N,1000));
        // 한 조합의 r,c에 대해 bfs 반복
        for(int j = 0; j < v.size(); j++){
            pair<int,int> p = v[j];
            int r = p.first;
            int c = p.second;
            // if(i == 1) cout << "현재 행:"<< r << " 현재 열:" << c << "\n";
            bfs(r,c);
            // if(i == 1)debug();
        }
        int result = getMin();
        if(result != -1) {
            min_time = min(min_time, result);
            anySuccess = true;   
        }

    }
    if(!anySuccess) cout << -1 << "\n";   // 진짜로 어떤 조합도 성공 못 했을 때만 -1
    else cout << min_time << "\n";

    return 0;
}