#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

vector<vector<int>> board;
int r, c, k;

bool cmp(pair<int,int> p1, pair<int,int> p2){
    if(p1.second != p2.second){
        return p1.second < p2.second;
    }
    else{
        return p1.first < p2.first;
    }
}

// 행 >= 열
void row(){
    int n = board.size();
    int m = board[0].size();
    vector<vector<int>> temp;
    int max_col = 0;

    // 맵에 각 값의 빈도수 저장하기.
    for(int i = 0 ; i < n; i++){
        // 행마다 생성 (숫자 - 빈도)
        map<int,int> num_m; 
        for(int j = 0; j < m; j++){
            int num = board[i][j];
            if(num == 0) continue;
            num_m[num]++;
            
        }

        // 행마다 처리하기 위함
        vector<pair<int,int>> v(num_m.begin(), num_m.end());
        sort(v.begin(), v.end(), cmp);
        vector<int> new_row;
        for(int k = 0; k < v.size(); k++){
            new_row.push_back(v[k].first);
            new_row.push_back(v[k].second);

            if (new_row.size() == 100) break;
        }
        max_col = max(max_col, (int)new_row.size());
        temp.push_back(new_row);
    }

    for(int i = 0; i < temp.size(); i++) {
        temp[i].resize(max_col, 0);
    }
    
    board = temp;

}

// 행 < 열
void col(){
    int n = board.size();
    int m = board[0].size();
    vector<vector<int>> temp;
    int max_row = 0;

    // 맵에 각 값의 빈도수 저장하기.
    for(int j = 0 ; j < m; j++){
        // 열마다 생성 (숫자 - 빈도)
        map<int,int> num_m; 
        for(int i = 0; i < n; i++){
            int num = board[i][j];
            if(num == 0) continue;
            num_m[num]++;
            
        }

        // 열마다 처리하기 위함
        vector<pair<int,int>> v(num_m.begin(), num_m.end());
        sort(v.begin(), v.end(), cmp);
        vector<int> new_col;
        for(int k = 0; k < v.size(); k++){
            new_col.push_back(v[k].first);
            new_col.push_back(v[k].second);

            if (new_col.size() == 100) break;
        }
        max_row = max(max_row, (int)new_col.size());
        temp.push_back(new_col);
    }

    for(int i = 0; i < temp.size(); i++) {
        temp[i].resize(max_row, 0);
    }

    // 배열 뒤집어 주기

    board.assign(max_row, vector<int>(temp.size(),0));
    
    for(int i = 0; i < temp.size(); i++){
        for(int j = 0; j < max_row; j++){
            board[j][i] = temp[i][j];
        }
    }


}

void debug(){
    for(int i = 0; i < board.size(); i++){
        for(int j = 0; j < board[0].size(); j++){
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "=========" << "\n";
}

int main() {
    cin >> r >> c >> k;
    board.assign(3, vector<int>(3, 0));
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            cin >> board[i][j];
        }
    }

    int t = 0;
    int n = board.size();
    int m = board[0].size();
    while(true){
        int n = board.size();
        int m = board[0].size();
        if((r - 1 < n) && (c - 1 < m)) {
            if(board[r - 1][c - 1] == k) break;
        }
        if(t == 100){
            t = -1; 
            break;
        }
        if(n >= m){
            row();
        } else {
            col();
        }
        
        t++; // 1초 증가
    }
    cout << t << "\n";
    

    return 0;
}