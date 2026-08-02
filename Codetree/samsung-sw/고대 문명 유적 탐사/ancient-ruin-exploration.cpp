#include <iostream>
#include <vector>
#include <queue>
#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> board;
vector<int> wall;
vector<pair<int,int>> middle;
pair<int,int> represent_middle;
int wall_idx = 0;
int K, M;
int dr[4] = {1, -1, 0, 0};
int dc[4] = {0, 0, 1, -1};
int total;

/*
// 시계방향 회전  (r,c) -> (c, r + N - 1)
// 중심 좌표 기준 3 x 3 회전
void rotate(int r, int c){
    vector<vector<int>> temp = board;
    for(int i = r - 1; i < r + 2; i++){
        for(int j = c - 1; j < c + 2 ; j++){
            board[j][i + 3 - 1] = temp[i][j];
        }
    }
}
*/

// ** 오답노트 **
void rotate(int r, int c){
    vector<vector<int>> temp = board;
    int sx = r - 1; // 3x3 영역의 시작 행
    int sy = c - 1; // 3x3 영역의 시작 열
    
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            // (i, j) -> (j, 2 - i) 로 90도 시계방향 회전 후 시작점(sx, sy) 더하기
            board[sx + j][sy + 2 - i] = temp[sx + i][sy + j];
        }
    }
}

void firstBfs(int r, int c){
    vector<vector<bool>> visited(5, vector<bool>(5, false));
    vector<pair<int,int>> temp; // 좌표들기록
    queue<pair<int,int>> q;
    temp.push_back({r,c});
    q.push({r,c});
    visited[r][c] = true;
    int cnt = 1;
    while(!q.empty()){
        auto [cur_r, cur_c] = q.front();
        q.pop();

        for(int d = 0; d < 4; d++){
            int nr = cur_r + dr[d];
            int nc = cur_c + dc[d];

            if(nr < 0 || nr >= 5 || nc < 0 || nc >= 5) continue;
            if(visited[nr][nc]) continue;
            
            if(board[cur_r][cur_c] == board[nr][nc]){
                visited[nr][nc] = true;
                q.push({nr,nc});
                temp.push_back({nr, nc}); // 발견한 유물을 바구니(temp)에 반드시 담아줌 **오답노트**
                cnt++;
            }
        }
    }
    if(cnt >= 3) {
        for(int i = 0; i < temp.size(); i++){
            auto [r,c] = temp[i];
            board[r][c] = 0;
        }
    }
}

// 유물의 개수가 몇 개인지 셈
int countReward(){
    int reward = 0;
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            if(board[i][j] == 0){
                reward += 1;
            }
        }
    }
    return reward;
}

// 벽면을 숫자로 채우기
void putWall(){
    for(int j = 0; j < 5; j++){
        for(int i = 4; i >= 0; i--){
            if(board[i][j] == 0) {
                board[i][j] = wall[wall_idx];
                wall_idx++;
            }
        }
    }
}

void initBoard(){
    board.assign(5, vector<int>(5,0));
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            cin >> board[i][j];
        }
    }
}

void init(){
    board.assign(5, vector<int>(5,0));
    wall.assign(M, 0);
    middle.push_back({1,1}); middle.push_back({1,2}); middle.push_back({1,3});
    middle.push_back({2,1}); middle.push_back({2,2}); middle.push_back({2,3});
    middle.push_back({3,1}); middle.push_back({3,2}); middle.push_back({3,3});

    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            cin >> board[i][j];
        }
    }

    for(int i = 0; i < M; i++){
        cin >> wall[i];
    }
}

bool cmp(tuple<int,int,int,int> t1, tuple<int,int,int,int> t2){
    // 유물 개수 많은 순
    if(get<2>(t1) != get<2>(t2)){
        return get<2>(t1) > get<2>(t2);
    }
    // 회전 각도 작은 순
    else if(get<3>(t1) != get<3>(t2)){
        return get<3>(t1) < get<3>(t2);
    }
    else if(get<1>(t1) != get<1>(t2)){
        return get<1>(t1) < get<1>(t2);
    }
    else{
        return get<0>(t1) < get<0>(t2);
    }
}

bool getRepresentMiddle(){
    vector<vector<int>> original_board = board; // 원본board 스냅샷 ** 오답노트 **
    represent_middle = {0,0};
    vector<tuple<int,int,int,int>> v; // r좌표, c좌표, 유물개수, 회전각도
    int mx = 0;

    // 회전 한 번 하고 보상 세기
    for(int i = 0; i < middle.size(); i++){
        board = original_board;
        auto [r,c] = middle[i];
        rotate(r,c);
        for(int j = 0; j < 5; j++){
            for(int k = 0; k < 5; k++){
                if(board[j][k] != 0) firstBfs(j,k);

            }
        }
        int reward = countReward();
        v.push_back({r, c, reward, 90});
    }

    // 회전 두 번 하고 보상 세기
    for(int i = 0; i < middle.size(); i++){
        board = original_board;
        auto [r,c] = middle[i];
        rotate(r,c);
        rotate(r,c);
        for(int j = 0; j < 5; j++){
            for(int k = 0; k < 5; k++){
                if(board[j][k] != 0) firstBfs(j,k);

            }
        }
        int reward = countReward();
        v.push_back({r, c, reward, 180});
    }

    // 회전 세 번 하고 보상 세기
    for(int i = 0; i < middle.size(); i++){
        board = original_board;
        auto [r,c] = middle[i];
        rotate(r,c);
        rotate(r,c);
        rotate(r,c);
        for(int j = 0; j < 5; j++){
            for(int k = 0; k < 5; k++){
                if(board[j][k] != 0) firstBfs(j,k);

            }
        }
        int reward = countReward();
        v.push_back({r, c, reward, 270});
    }

    // 선택 기준대로 정렬
    sort(v.begin(), v.end(), cmp);

    int best_reward = get<2>(v[0]);
    if(best_reward == 0) return false; // 획득할 유물이 전혀 없다면 false 반환 ** 오답노트**

    board = original_board;

    int best_r = get<0>(v[0]);
    int best_c = get<1>(v[0]);
    int best_angle = get<3>(v[0]);
    
    // 진짜 회전 적용 ** 오답노트**
    int rotate_cnt = best_angle / 90;
    for(int i = 0; i < rotate_cnt; i++) {
        rotate(best_r, best_c);
    }
    
    represent_middle = {best_r, best_c};
    return true; // 성공적으로 찾았음을 반환


    // 생각할 것은 board 계속 누적되는데 이거 상태 초기화 해줘야 할 듯  ** 오답노트 **

}

bool keepExplore(){
    bool keep = false;
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            if(board[i][j] == 0) keep = true;
        }
    }
    return keep;
}

/*
void explore(){
    while(keepExplore()){
        firstBfs(represent_middle.first, represent_middle.second);
        int reward = countReward();
        total += reward;
        putWall();
    }
}
*/

// **오답노트**
void explore(){
    while(true){
        // 1. 맵 전체를 스캔하며 3개 이상 모인 유물을 전부 터뜨리기 (0으로 만들기)
        for(int i = 0; i < 5; i++){
            for(int j = 0; j < 5; j++){
                if(board[i][j] != 0) {
                    firstBfs(i, j);
                }
            }
        }
        
        // 2. 터진 유물(0이 된 칸) 개수 세기
        int reward = countReward();
        
        // 3. 더 이상 터진 유물이 없다면 연쇄 반응 종료!
        if(reward == 0) break; 
        
        total += reward;
        
        // 4. 비워진 자리에 벽면 조각 채워넣기
        putWall();
    }
}


int main() {
    cin >> K >> M;
    init();

    // K번 반복
    for(int i = 0; i < K; i++){
        total = 0;
        if(!getRepresentMiddle()) break; // **오답노트**
        explore();
        cout << total;
        if(i < K - 1) cout << " ";
    }

    return 0;
}