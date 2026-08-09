#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int N, M, K;
vector<vector<int>> board;
pair<int,int> door; // 현재 출구 좌표
int sum;
vector<pair<int, int>> people; // 사람들의 위치

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

int getDistance(int r, int c, int nr, int nc){
    return abs(nr-r) + abs(nc - c);
}

bool isRange(int r, int c){
    if(r < 0 || r >= N || c < 0 || c >= N) return false;
    return true;
}

// 사람 움직이기
void movePeople(){
    // **사람을 배열로 관리해야 함**
    for(int i = 0; i < people.size(); i++){
        if(people[i].first == -1) continue;

        int cur_r = people[i].first;
        int cur_c = people[i].second;
        int cur_dist = getDistance(cur_r, cur_c, door.first, door.second);
        int next_r = cur_r, next_c = cur_c;

        for(int d = 0; d < 4; d++){
            int nr = cur_r + dr[d];
            int nc = cur_c + dc[d];
            
            
            // 격자 밖이거나 벽(1 이상)이 있으면 패스
            if (!isRange(nr, nc) || board[nr][nc] > 0) continue;
            
            int next_dist = getDistance(nr, nc, door.first, door.second);

            if (next_dist < cur_dist) {
                next_r = nr;
                next_c = nc;
                break; // 상하좌우 순서대로 탐색하므로, 찾자마자 break 하면 조건(우선순위) 자동 만족 함
            }
        }

        // 이동한 경우 갱신
        if (next_r != cur_r || next_c != cur_c) { 
            people[i] = {next_r, next_c};
            sum++; // 한 명 이동할 때마다 거리 + 1
            
            // 이동했는데 출구에 도착한 경우 탈출 처리
            if (next_r == door.first && next_c == door.second) {
                people[i] = {-1, -1}; 
            }
        }

    }
    /*
    // **오답노트**
    vector<vector<int>> temp_board = board;

    // **오답노트**
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            if(temp_board[i][j] == 88) temp_board[i][j] = 0;
        }
    }
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            // 사람 발견하면
            if(board[i][j] == 88){
                vector<pair<int,int>> candidates; // 갈 수 있는 거리 후보들
                int cur_r = i;
                int cur_c = j;
                // 현재 출구까지의 거리
                int cur_distance = getDistance(cur_r, cur_c, door.first, door.second); 

                for(int d = 0; d < 4; d++){
                    int nr = cur_r + dr[d];
                    int nc = cur_c + dc[d];
                    int next_distance = getDistance(nr, nc, door.first, door.second);

                    // 범위 벗어나거나 벽인 경우 무시
                    if(!isRange(nr,nc) || board[nr][nc] > 0) continue;
                    // 최단 거리가 가까운 경우에만
                    if(next_distance < cur_distance) candidates.push_back({nr,nc});
                }
                if(!candidates.empty()){
                    sum += 1;
                    int nr = candidates[0].first;
                    int nc = candidates[0].second;
                    // 출구가 아닌 경우에만 이동
                    // temp에 그리기 **오답노트**
                    if(board[nr][nc] != -1)
                    {
                        temp_board[nr][nc] = 88;
                    }
                    // 이동할 곳 없다면 그대로 그리기
                    else{
                        temp_board[i][j] = 88;
                    }
                    
                }
            }
            
        }
    }
    board = temp_board;
    */
}

// 가장 작은 정사각형 찾고 회전하기
void rotate(){
    int n = 2; //제일 처음 한 변의 길이
    tuple<int,int,int> left_top; // 좌표와 크기
    bool found = false;
    while(n <= N){
        // 모든 정사각형 순회
        for(int i = 0; i <= N - n; i++){
            for(int j = 0; j <= N - n; j++){
                bool hasDoor = false;
                bool hasPerson = false;
                // **오답노트** i + n
                for(int row = i; row < i + n; row++){
                    for(int col = j; col < j + n; col++){
                        if(row == door.first && col == door.second) {
                        hasDoor = true;
                        }
                        // 현재 칸에 사람이 있는지 확인
                        for(auto p : people){
                            if(p.first == -1) continue; // 탈출한 사람 무시
                            if(p.first == row && p.second == col) {
                                hasPerson = true;
                            }
                        }
                    }
                }
                if(hasPerson && hasDoor) {
                    left_top = {i,j,n};
                    found = true;
                    break;
                }
            }
            if(found) break;
        }
        if(found) break;
        n++;
    }
    
    // 진짜 회전 시계 i,j = j, n-1-i
    vector<vector<int>> temp = board;
    int sr = get<0>(left_top); 
    int sc = get<1>(left_top);
    int size = get<2>(left_top); //정사각형 한 변의 길이

    // 보드 회전
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            board[sr + j][sc + size - 1 - i] = temp[sr + i][sc + j];
        }
    }
    // **사람도 회전시켜주기**
    for(int p = 0; p < people.size(); p++){
        if(people[p].first == -1) continue;
        int pr = people[p].first;
        int pc = people[p].second;
        // 정사각형 범위 안에 있는 사람만 회전
        if(pr >= sr && pr < sr + size && pc >= sc && pc < sc + size){
            people[p].first = sr + (pc - sc);
            people[p].second = sc + size - 1 - (pr - sr);
        }
    }

    // 1씩 깎고 출구 갱신
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            // 깎고 갱신하는 것도 (sr, sc) 기준
            int row = sr + i;
            int col = sc + j;
            if(board[row][col] > 0 && board[row][col] < 10) board[row][col] -= 1;
            if(board[row][col] == -1) door = {row, col};
        }
    }
    

}

void init(){
    sum = 0;
    cin >> N >> M >> K;
    board.assign(N, vector<int>(N, 0));
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cin >> board[i][j];
        }
    }
    
    for(int i = 0; i < M; i++){
        int r,c;
        cin >> r >> c;
        r -=1; c-=1;
        people.push_back({r,c});
    }

    // 출구좌표 = -1
    int exit_r, exit_c;
    cin >> exit_r >> exit_c;
    exit_r -= 1; exit_c -=1;
    door = {exit_r, exit_c};
    board[exit_r][exit_c] = -1;
}

void debug(){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "================" << "\n";
}

bool everyExit(){
    for(auto p : people){
        if(p.first != -1) return false; // 아직 탈출 안 한 사람이 있다면
    }
    return true;
}

int main() {
    init();
    
    for(int i = 0; i < K; i++){
        movePeople();
        if(everyExit()) break;
        rotate();

    }
    cout << sum << "\n" << door.first + 1 << " " << door.second + 1 << "\n";

    // Please write your code here.
    return 0;
}