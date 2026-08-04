#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int n, m, k; // 격자 크기, 원자 개수, 실험 시간

struct Atom{
    int m; // 질량
    int s; // 속력
    int d; // 방향
};

vector<Atom> board[51][51];

// 상 우 하 좌 0, 2, 4, 6  // 1, 3, 5, 7 대각선들
int dr[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dc[8] = {0, 1, 1, 1, 0, -1, -1, -1};

void init(){
    cin >> n >> m >> k;
    for(int i = 0; i < m; i++){
        int r, c, m, s, d;
        cin >> r >> c >> m >> s >> d;
        r -= 1;
        c -= 1;
        board[r][c].push_back({m,s,d});
    }
}

int moveR(int r, int step){
    int new_r;
    step = step % n;
    new_r = (r + step + n) % n;
    return new_r;
}

int moveC(int c, int step){
    int new_c;
    step = step % n;
    new_c = (c + step + n) % n;
    return new_c;
}

void changeArray(vector<Atom> temp[51][51]){
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            board[i][j] = temp[i][j]; 
        }
    }
}

// 격자들 이동
void move(){
    vector<Atom> temp[51][51];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(board[i][j].size() == 0) continue;
            
            while(board[i][j].size() > 0){
                Atom a = board[i][j].back();
                board[i][j].pop_back();
                int m = a.m;
                int s = a.s;
                int d = a.d;
                int new_r = moveC(i, dr[d] * s);
                int new_c = moveR(j, dc[d] * s);
                temp[new_r][new_c].push_back({m, s, d});
            }
        }
    }
    changeArray(temp);
}

void merge(){
    vector<Atom> temp[51][51];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(board[i][j].size() >= 2){
                int size = board[i][j].size();
                int dir = board[i][j][0].d; // 제일 처음의 방향
                int new_m = 0;
                int new_s = 0;
                bool all_same = true;
                for(Atom a : board[i][j]){
                    new_m += a.m;
                    new_s += a.s;
                    if(dir == 0 || dir == 2 || dir == 4 || dir == 6){
                        if(a.d == 1 || a.d == 3 || a.d == 5 || a.d == 7){
                            all_same = false;
                        }
                    }
                    if(dir == 1 || dir == 3 || dir == 5 || dir == 7){
                        if(a.d == 0 || a.d == 2 || a.d == 4 || a.d == 6){
                            all_same = false;
                        }
                    }

                }
                new_m /= 5;
                new_s /= size;
                if(new_m == 0) continue;
                if(all_same){
                    dir = 0;
                }
                else{
                    dir = 1;
                }
                temp[i][j].push_back({new_m, new_s, dir});
                temp[i][j].push_back({new_m, new_s, dir + 2});
                temp[i][j].push_back({new_m, new_s, dir + 4});
                temp[i][j].push_back({new_m, new_s, dir + 6});
            }
            // 오답노트
            else if(board[i][j].size() == 1) {
                temp[i][j].push_back(board[i][j][0]);
            }
        }
    }
    changeArray(temp);
}

void getSum(){
    int sum = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(board[i][j].size() > 0){
                for(Atom a : board[i][j]){
                    sum += a.m;
                }
            }
        }
    }
    cout << sum << "\n";
}

int main() {
    init();
    while(k > 0){
        move();
        merge();
        k--;
    }
    getSum();
    
    return 0;
}