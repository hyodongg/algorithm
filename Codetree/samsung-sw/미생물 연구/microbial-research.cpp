#include <iostream>
using namespace std;
#include <bits/stdc++.h>
// 16:00

int N, Q;
vector<vector<int>> board;
vector<tuple<int,int,int,int>> bacteria;
int group_idx = 0;
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

struct Group{
    int r;
    int c;
    int g_size;
};

// groups[0] = 0번 그룹의 좌표들 (행, 열, 그룹사이즈)
vector<vector<Group>> groups;

void debug(){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "==============" << "\n";
}

bool isRange(int r, int c){
    if(r < 0 || r >= N || c < 0 || c >= N) return false;
    return true;
}

bool checkArea(int g_num, int r, int c, vector<vector<int>> temp, vector<vector<bool>> visited){
    int total_cnt = 0;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(temp[i][j] == g_num) total_cnt += 1;
        }
    }

    queue<pair<int,int>> q;
    q.push({r,c});
    visited[r][c] = true;
    int cnt = 0;
    while(!q.empty()){
        auto [cur_r, cur_c] = q.front();
        cnt += 1;
        q.pop();
        for(int d = 0; d < 4; d++){
            int nr = cur_r + dr[d];
            int nc = cur_c + dc[d];
            if(!isRange(nr,nc)) continue;
            if(!visited[nr][nc] && temp[nr][nc] == g_num ){
                visited[nr][nc] = true;
                q.push({nr,nc});
            }

        }
    }
    if(cnt == total_cnt) return true;
    else return false;
}

void insertBacteria(){
    vector<vector<int>> temp = board;
    // 박테리아 넣기
    auto [r1, c1, r2, c2] = bacteria[group_idx];
    int g_size = abs(r2 - r1) * abs(c2 -c1);
    for(int i = r1; i < r2; i++){
        for(int j = c1; j < c2; j++){
            temp[i][j] = group_idx;
            groups[group_idx].push_back({i,j,g_size});
        }
    }

    // 맵이 갱신되었으니 옛날 좌표들은 싹 지우고, 새로 기록해야함
    for(int i = 0; i <= group_idx; i++){
        groups[i].clear();
    }
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(temp[i][j] != -1){
                // 살아있는 진짜 좌표들만 그룹에 다시 넣어줍니다.
                groups[temp[i][j]].push_back({i, j, 0}); 
            }
        }
    }

    
    // 그룹 나눠지는지 확인 후 나눠졌으면 제거
    vector<vector<bool>> visited(N, vector<bool>(N, false));
    for(int i = 0; i < group_idx; i++){
        if(!groups[i].empty()){
            bool isAlive = checkArea(i, groups[i][0].r, groups[i][0].c, temp, visited);
            // 나눠져 있다면 삭제
            if(!isAlive){
                groups[i].clear();
                for(int row = 0; row < N; row++){
                    for(int col = 0; col < N; col++){
                        if(temp[row][col] == i) temp[row][col] = -1;
                    }
                }
            }
        }
    }

    group_idx += 1;

    
    board = temp;
}

bool cmp(int a, int b){
    if(groups[a].size() != groups[b].size()){
        return groups[a].size() > groups[b].size();
    }
    else{
        return a < b;
    }
}

void moveBacteria(){
    vector<int> alive_groups;
    for(int i = 0; i < group_idx; i++){
        if(!groups[i].empty()) alive_groups.push_back(i);
    }
    // 어느 그룹부터 옮길지
    sort(alive_groups.begin(), alive_groups.end(), cmp);

    // 새로 배양할 판
    vector<vector<int>> new_board(N, vector<int>(N, -1));

    for(int i = 0; i < alive_groups.size(); i++){
        int target_group = alive_groups[i]; // 예를들어 2번째 그룹이 제일 먼저라면 이거부터 겠지
        auto& cells = groups[target_group]; //현재 그룹의 모든 미생물 좌표

        // 내가 놓을 그룹의 최소 r,c값 구하기
        int min_r = 1e9, min_c = 1e9;
        for(auto cell: cells){
            min_r = min(min_r, cell.r);
            min_c = min(min_c, cell.c);
        }

        // 자리에 놓을 수 있는가? 최종 생존 여부
        bool is_placed = false;

        for(int tr = 0; tr < N && !is_placed; tr++){
            for(int tc = 0; tc < N && !is_placed; tc++){
                bool can_stamp = true; // 현재 자리에 놓을대 모든 박테리아가 들어갈 수 있는가?

                for(auto& cell : cells){
                    int diff_r = cell.r - min_r;
                    int diff_c = cell.c - min_c;

                    int nr = tr + diff_r;
                    int nc = tc + diff_c;

                    if(!isRange(nr,nc) || new_board[nr][nc] != -1){
                        can_stamp = false;
                        break;
                    }
                }
                //성공했다면 진짜 찍기
                if(can_stamp){
                    is_placed = true;
                    for(auto& cell : cells){
                        int diff_r = cell.r - min_r;
                        int diff_c = cell.c - min_c;

                        //원본(groups)좌표를 새 위치로 갱신
                        cell.r = tr + diff_r;
                        cell.c = tc + diff_c;

                        // 맵에 그룹 이름 다시 새기기
                        new_board[cell.r][cell.c] = target_group;
                    }
                }
            }
        }

        if(!is_placed){
            cells.clear();
        }
    }
    board = new_board;
}

void getSum(){  
    set<pair<int,int>> adj_pairs;
    int total_score = 0;

    // 보드판 전체 순회
    for(int r = 0; r < N; r++){
        for(int c = 0; c < N; c++){
            int me = board[r][c];
            if(me == -1) continue; // 빈칸이면 패스

            // 4방향 쳐다보기
            for(int d = 0; d < 4; d++){
                int nr = r + dr[d];
                int nc = c + dc[d];

                if(!isRange(nr, nc)) continue;
                
                int neighbor = board[nr][nc];
                
                // 이웃 칸에 나랑 다른 미생물이 살고 있다면? 인접!
                if(neighbor != -1 && me != neighbor){
                    // 무조건 작은 번호가 앞에 오게 만들어서 set에 넣기 (A-B나 B-A나 똑같이 취급)
                    int u = min(me, neighbor);
                    int v = max(me, neighbor);
                    adj_pairs.insert({u, v});
                }
            }
        }
    }

    for(auto a : adj_pairs){
        int g1 = a.first;
        int g2 = a.second;
        total_score += groups[g1].size() * groups[g2].size();
    }
    cout << total_score << "\n";
}

void init(){
    cin >> N >> Q;
    board.assign(N, vector<int>(N, -1));
    groups.resize(Q);
    for(int i = 0; i < Q; i++){
        int r1,c1,r2,c2;
        cin >> r1 >> c1 >> r2 >> c2;
        bacteria.push_back({r1,c1,r2,c2});
    }
}

int main() {
    init();
    for(int i = 0; i < Q; i++){
        insertBacteria();
        moveBacteria();
        getSum();
    }

    // Please write your code here.
    return 0;
}