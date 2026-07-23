#include<iostream>
#include <vector>
#include <queue>

using namespace std;

int dr[4] = {1, -1, 0, 0};
int dc[4] = {0, 0, -1, 1};

void solve(int tc){
    vector<vector<int>> board(16,vector<int>(16,0));
    int start_r, start_c;
    int end_r, end_c;
    vector<vector<bool>> visited(16, vector<bool>(16,false));
    queue<pair<int,int>> q;
    // board초기화 및 시작/끝 지점 파악
    for(int i = 0; i < 16; i++){
        string row;
        cin >> row;
        for(int j = 0; j < 16; j++){
            board[i][j] = row[j] - '0';
            if(board[i][j] == 2){
                start_r = i;
                start_c = j;
            }
            if(board[i][j] == 3){
                end_r = i;
                end_c = j;
            }
        }
    }
        q.push({start_r, start_c});
        visited[start_r][start_c] = true;
        
        while(!q.empty()){
            pair<int,int> p = q.front();
            int cur_r = p.first;
            int cur_c = p.second;
            q.pop();
            
            for(int d = 0; d < 4; d++){
                int nr = cur_r + dr[d];
                int nc = cur_c + dc[d];
                
                if(nr < 0 || nr >= 16 || nc < 0 || nc >= 16) continue;
                if(visited[nr][nc]) continue;
               	if(board[nr][nc] == 1) continue;
                
                q.push({nr, nc});
                visited[nr][nc] = true;
            }
        }
    if(visited[end_r][end_c]) cout << "#" << tc << " " << 1 << "\n";
    else cout << "#" << tc << " " << 0 << "\n";
}

int main(int argc, char** argv)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	int test_case;
	/*
	   여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
	*/
	while(cin >> test_case){
        solve(test_case);
    }
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}