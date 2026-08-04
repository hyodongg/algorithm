#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n;
vector<vector<int>> board;
vector<vector<int>> groupnum_board;
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};
vector<pair<int,int>> groupComb;
vector<int> temp;
int sum;
int group_num;


struct Group{
    int g_num; // 그룹 넘버
    int r;
    int c;
    int num; // 그룹을 이루고 있는 숫자
};

// groups[0] = G0의 좌표들
// groups[1] = G1의 좌표들
vector<vector<Group>> groups;
vector<vector<bool>> visited;

bool isRange(int r, int c){
    if(r < 0 || r >= n || c < 0 || c >= n) return false;
    return true;
}

void makeGroup(int r, int c, vector<vector<bool>>& visited){
    vector<Group> one_group;
    int num = board[r][c];
    queue<pair<int,int>> q;
    visited[r][c] = true;
    q.push({r,c});
    while(!q.empty()){
        auto [cur_r, cur_c] = q.front();
        groupnum_board[cur_r][cur_c] = group_num;
        one_group.push_back({group_num, cur_r, cur_c, num});
        q.pop();
        
        for(int d = 0; d < 4; d++){
            int nr = cur_r + dr[d];
            int nc = cur_c + dc[d];
            
            if(!isRange(nr, nc)) continue;

            if(board[nr][nc] == num && !visited[nr][nc]){
                visited[nr][nc] = true;
                q.push({nr, nc});
            }
        }
    }
    groups.push_back(one_group);
}

// 그룹들의 조합
void groupCombination(int depth, int idx){
    if(depth == 2){
        int g1 = temp[0];
        int g2 = temp[1];
        groupComb.push_back({g1,g2});
        return;
    }

    for(int i = idx; i < groups.size(); i++){
        temp.push_back(i);
        groupCombination(depth + 1, i + 1);
        temp.pop_back();
    }

}

// 겹치는 선분의 수 구하기
int countLine(const vector<Group>& g1, const vector<Group>& g2){
    int cnt = 0;
    int g1_num = g1[0].num;
    int g1_gnum = g1[0].g_num;
    int g2_num = g2[0].num;
    int g2_gnum = g2[0].g_num;
    for(int i = 0; i < g1.size(); i++){
        int cur_r = g1[i].r;
        int cur_c = g1[i].c;

        for(int d = 0; d < 4; d++){
            int nr = cur_r + dr[d];
            int nc = cur_c + dc[d];
            if(!isRange(nr,nc)) continue;
            // 그룹 넘버도 같아야하는데,,
            if((board[nr][nc] == g2_num) && g2_gnum == groupnum_board[nr][nc]) cnt++;
        }
    }
    return cnt;
}

// 두 개의 그룹 합 - 그룹 넘버로 넘긺
void calculateSum(int group1, int group2){
    vector<Group> g1 = groups[group1];
    vector<Group> g2 = groups[group2];
    int same_line = countLine(g1, g2);
    if(same_line != 0){
        sum += ((int)g1.size() + (int)g2.size()) * (g1[0].num) * (g2[0].num) * same_line;
    }
    /*
    cout << "그룹1크기:" << (int)g1.size() << " "
    << "그룹2크기:" << (int)g2.size() << " "
    << "그룹1숫자값:"<< g1[0].num << " " 
    << "그룹2숫자값:" << g2[0].num << " " 
    << "맞닿은 변 수:" << same_line;
    cout << "\n";
    cout << sum << "\n";
    */

}

void init(){
    sum = 0;
    cin >> n;
    board.assign(n, vector<int>(n, 0));
    groupnum_board.assign(n, vector<int>(n, -1));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> board[i][j];
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
    cout << "===========" << "\n";

}

void debugGroupnum(){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << groupnum_board[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "===========" << "\n";
}

// 십자가 반시계 회전
void rotateRclock(){
    int mid = n / 2;
    vector<vector<int>> temp = board;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(i == mid || j == mid){
                board[n - 1 - j][i] = temp[i][j];
            } 
        }
    }
}

// 부분배열 4개 시계 회전
void rotateClock(){
    vector<vector<int>> temp = board;
    int sr = 0;
    int sc = 0;
    int interval = n / 2 + 1;
    int new_n = n / 2;
    for(int i = 0; i < new_n; i++){
        for(int j = 0; j < new_n; j++){
            board[j][new_n - 1 - i] = temp[i][j];
            board[j][interval + new_n - 1 - i] = temp[i][interval + j];
            board[interval + j][new_n - 1 - i] = temp[interval + i][j];
            board[interval + j][interval + new_n - 1 - i] = temp[interval + i][interval + j];
        }
    }

}


//반시계 방향 한 번 회전 후 부분배열 4개 시계방향 2번회전
void rotate(){
    rotateRclock();
    rotateClock();
}

int main() {
    int t = 4;
    init();
    while(t > 0){
        groups.clear();
        groupComb.clear();
        // 처음 방문배열 초기화
        group_num = 0;
        visited.assign(n, vector<bool>(n, false));
        groupnum_board.assign(n, vector<int>(n, -1));
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(!visited[i][j]){
                    makeGroup(i, j, visited);
                    group_num++;
                }
            }
        }
        // debugGroupnum();
        groupCombination(0, 0);
        for(int i = 0; i < groupComb.size(); i++){
            pair<int,int> p = groupComb[i];
            calculateSum(p.first, p.second);
        }
        rotate();
        t--;
    }
    cout << sum << "\n";

    
    // Please write your code here.
    return 0;
}