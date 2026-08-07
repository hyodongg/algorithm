#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int N, K, L;
// -1: 물건

vector<pair<int,int>> cleaners; // 청소기 좌표 clearners[0] = (4,3);
vector<vector<int>> board;
int dr[4] = {0, 1, 0, -1}; // 오, 아, 왼, 위
int dc[4] = {1, 0, -1, 0};

bool isRange(int r, int c){
    if(r < 0 || r >= N || c < 0 || c >= N) return false;
    return true;
}

bool isBlock(int r, int c){
    if(board[r][c] == -1) return true;
    return false;
}

bool cmp(tuple<int,int,int> t1, tuple<int,int,int> t2){
    if(get<0>(t1) != get<0>(t2)){
        return get<0>(t1) < get<0>(t2);
    }
    else if(get<1>(t1) != get<1>(t2)){
        return get<1>(t1) < get<1>(t2);
    }
    else{
        return get<2>(t1) < get<2>(t2);
    }
}

void moveCleaners(){
    int size = cleaners.size();
    for(int i = 0; i < cleaners.size(); i++){
        vector<vector<bool>> has_cleaner(N, vector<bool>(N, false));
        // 나 제외한 청소기 위치 등록
        for(int j = 0; j < size; j++){
            if(i == j) continue;
            has_cleaner[cleaners[j].first][cleaners[j].second] = true;
        }
        pair<int,int> cleaner = cleaners[i];
        int r = cleaner.first;
        int c = cleaner.second;
        queue<pair<int,int>> q;
        vector<vector<int>> dist(N, vector<int>(N, -1));
        q.push({r, c});
        dist[r][c] = 0;

        vector<tuple<int,int,int>> v; // {거리, 행, 열}

        // 현재 서있는 위치에 이미 먼지가 있다면 거리 0으로 후보 등록
        if(board[r][c] > 0){
            v.push_back({0, r, c});
        }

        while(!q.empty()){
            auto [cur_r, cur_c] = q.front();
            q.pop();

            for(int d = 0; d < 4; d++){
                int nr = cur_r + dr[d];
                int nc = cur_c + dc[d];

                // 범위 밖, 벽, 청소기, 이미 방문한 곳
                if(!isRange(nr, nc) || isBlock(nr, nc) || has_cleaner[nr][nc] || dist[nr][nc] != -1) continue;

                dist[nr][nc] = dist[cur_r][cur_c] + 1;
                q.push({nr, nc});
                
                // 먼지 발견 시 후보군에 추가
                if(board[nr][nc] > 0){
                    v.push_back({dist[nr][nc], nr, nc});
                }
            }
        }
        // 가장 가까운(거리 최소) -> 행 작은 -> 열 작은 순으로 정렬 후 이동
        if(!v.empty()){
            sort(v.begin(), v.end(), cmp);
            cleaners[i] = {get<1>(v[0]), get<2>(v[0])};
        }
    }
}

void clean(){
    for(int i = 0; i < cleaners.size(); i++){
        pair<int,int> cleaner = cleaners[i];
        int cur_r = cleaner.first;
        int cur_c = cleaner.second;

        int max_dust = -1;
        int best_dir = -1;
        
        // 4가지 방향 바라보는 시뮬레이션
        for(int d = 0; d < 4; d++){ //우, 하, 좌, 상
            int cur_dust = 0;
            
            cur_dust = min(board[cur_r][cur_c], 20);

            int direct[3] = {d, (d + 1) % 4, (d + 3) % 4};
            for(int k = 0; k < 3; k++){
                int nd = direct[k];
                int nr = cur_r + dr[nd];
                int nc = cur_c + dc[nd];

                if(isRange(nr, nc) && !isBlock(nr, nc)){
                    cur_dust += min(board[nr][nc], 20);
                }
            }
            if(cur_dust > max_dust){
                max_dust = cur_dust;
                best_dir = d;
            }
        }

        // 실제 청소 실행
        board[cur_r][cur_c] -= min(board[cur_r][cur_c], 20);
        int direct[3] = {best_dir, (best_dir + 1) % 4, (best_dir + 3) % 4};
        for(int k = 0; k < 3; k++){
            int nd = direct[k];
            int nr = cur_r + dr[nd];
            int nc = cur_c + dc[nd];
            if(isRange(nr, nc) && !isBlock(nr, nc)){
                board[nr][nc] -= min(board[nr][nc], 20);
            }
        }
    }
}

void plusDust(){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(board[i][j] > 0){
                board[i][j] += 5;
            }
        }
    }
}

void debugCleaners(){
    for(int i = 0; i < cleaners.size(); i++){
        cout << "(" << cleaners[i].first << "," << cleaners[i].second << ") ";
    }
    cout << "\n";
}

void spreadDust(){
    // 원본 보드 스냅샷 찍기
    vector<vector<int>> temp_board = board;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(board[i][j] != 0) continue;
            int dust = 0;
            for(int d = 0; d < 4; d++){
                int nr = i + dr[d];
                int nc = j + dc[d];
                // 4방향에 범위 안넘었고 막히지 않았고 
                if(isRange(nr,nc) && !isBlock(nr,nc) && board[nr][nc] > 0) {
                    dust += board[nr][nc];
                }
                
            }
            temp_board[i][j] += (dust / 10);
        }
    }
    board = temp_board;
}

void getDust(){
    int sum = 0;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(board[i][j] > 0) sum += board[i][j];
        }
    }

    if(sum == 0) cout << 0 << "\n";
    cout << sum << "\n";
}

void debug(){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "===================" << "\n";
}

void init(){
    cin >> N >> K >> L;
    board.assign(N, vector<int>(N, 0));
    cleaners.assign(K, pair<int,int>());
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cin >> board[i][j];
        }
    }
    for(int i = 0; i < K; i++){
        int r, c;
        cin >> r >> c;
        r -= 1; c -= 1;
        cleaners[i] = {r,c};
    }
}

int main() {
    init();

    for(int i = 0; i < L; i++){
        moveCleaners();
        clean();
        //debug();
        plusDust();
        //debug();
        spreadDust();
        //debug();
        getDust();
    }
    
    return 0;
}