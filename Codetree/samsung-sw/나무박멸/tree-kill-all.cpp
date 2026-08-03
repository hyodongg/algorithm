#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int n, m, k, c;
int total;
vector<vector<int>> board;
vector<vector<int>> medicine;
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

int dr2[4] = {-1, -1, 1, 1}; //왼쪽위 오른쪽위 왼쪽아래 오른쪽아래
int dc2[4] = {-1, 1, -1, 1};

void init(){
    total = 0;
    cin >> n >> m >> k >> c;
    board.assign(n, vector<int>(n,0));
    medicine.assign(n, vector<int>(n, 0));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> board[i][j];
        }
    }
}

bool isRange(int r, int c){
    if(r < 0 || r >= n || c < 0 || c >= n) return false;
    return true;
}

void growth(){
    vector<vector<int>> tree(n, vector<int>(n, 0)); // 주변에 나무가 몇개 있는지
    vector<vector<int>> blank(n, vector<int>(n,0)); // 주변에 몇개의 번식가능한 칸이 있는지
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            int cnt = 0;
            int blank_cnt = 0;
            for(int d = 0; d < 4; d++){
                int nr = i + dr[d];
                int nc = j + dc[d];
                
                if(!isRange(nr,nc)) continue;
                if(board[nr][nc] == -1) continue;

                // 현재 칸에 나무가 있고 주변에 나무가 있는 경우
                if(board[i][j] > 0 && board[nr][nc] > 0) cnt++;

                // 현재 칸에 나무가 있고, 다음 칸이 비어있으며 제초제가 없는 경우
                if(board[i][j] > 0 && board[nr][nc] == 0 && medicine[nr][nc] == 0)  blank_cnt++;
            }
            tree[i][j] = cnt;
            blank[i][j] = blank_cnt;
        }
    }

    // 성장
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(board[i][j] > 0)
            board[i][j] += tree[i][j];
        }
    }

    // 번식
    vector<vector<int>> plus_tree(n, vector<int>(n,0)); // 번식 얼마나 해야하는지
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){

            for(int d = 0; d < 4; d++){
                int nr = i + dr[d];
                int nc = j + dc[d];
                
                if(!isRange(nr,nc)) continue;

                // 채우고자 하는 곳이 빈칸이며 약이 없어야 함
                if(board[nr][nc] == 0 && !medicine[nr][nc]){
                    // 현재 나무 / 현재 빈칸으로 다음칸을 채움
                    if(blank[i][j] != 0){
                        plus_tree[nr][nc] += board[i][j] / blank[i][j];
                    }
                }
            }
        }
    }

    // board에 반영
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            board[i][j] += plus_tree[i][j];
        }
    }
}

// 제초제 기한 줄이기
void decreaseMedicine() {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            // 제초제 잔여 기한이 남아있다면 1 감소
            if(medicine[i][j] > 0) {
                medicine[i][j]--;
            }
        }
    }
}

void debug(){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "==================" << "\n";
}


void erase(){

    // 최적을 찾기 위해 **오답노트**
    int max_del = -1;
    int best_r = -1;
    int best_c = -1;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            // 나무가 있는 칸에서만 제초제를 뿌릴 수 있음. ** 오답노트 **
            if(board[i][j] <= 0) continue;

            int cnt = board[i][j];
            for(int d = 0; d < 4; d++){
                for(int repeat = 1; repeat <= k; repeat++){
                    int nr = i + dr2[d] * repeat;
                    int nc = j + dc2[d] * repeat;

                    if(!isRange(nr,nc)) break;
                    if(board[nr][nc] <= 0) break; // 벽이거나 빈칸이면 전파 중단

                    cnt += board[nr][nc];
                }
            }
            // 최적 위치 갱신
            if(cnt > max_del){
                max_del = cnt;
                best_r = i;
                best_c = j;
            }
            else if(cnt == max_del){
                if(i < best_r){
                    best_r = i;
                    best_c = j;
                } else if(i == best_r && j < best_c){
                    best_c = j;
                }
            }
        }
    }

    // 박멸할 나무가 아예 없는 경우 조기 종료
    if(best_r == -1) return; 

    // 실제 제초제 살포 (타이머 c로 설정)
    // 그 전에 벤 나무 더함
    total += board[best_r][best_c];
    board[best_r][best_c] = 0;
    medicine[best_r][best_c] = c;

    for(int d = 0; d < 4; d++) {
        for(int repeat = 1; repeat <= k; repeat++) {
            int nr = best_r + dr2[d] * repeat;
            int nc = best_c + dc2[d] * repeat;

            if(!isRange(nr, nc)) break;

            // 빈칸이거나 벽인 경우: 그 칸까지만 제초제를 뿌리고 중단
            if(board[nr][nc] <= 0) {
                medicine[nr][nc] = c;
                break; 
            }

            // 나무가 있는 칸인 경우: 나무를 지우고 제초제 살포
            total += board[nr][nc];
            board[nr][nc] = 0;
            medicine[nr][nc] = c;
        }
    }
}

void getTotal(){
    cout << total;
}

int main() {   
    init();
    for(int i = 0; i < m; i++){
        growth();
        decreaseMedicine();
        erase();
    }
    getTotal();


    // Please write your code here.
    return 0;
}