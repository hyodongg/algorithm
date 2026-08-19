#include <string>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

bool isRange(int r, int c) {
    return r >= 0 && r < 5 && c >= 0 && c < 5;
}

bool bfs(int start_r, int start_c, const vector<string>& place) {
    vector<vector<bool>> visited(5, vector<bool>(5, false));
    queue<tuple<int, int, int>> q; // {r, c, 현재까지의 거리}
    
    q.push({start_r, start_c, 0});
    visited[start_r][start_c] = true;
    
    while(!q.empty()) {
        auto [r, c, dist] = q.front();
        q.pop();
        
        // 거리가 2 초과면 더 이상 탐색할 필요 없음 (가지치기)
        if(dist >= 2) continue; 
        
        // 상하좌우 4방향 탐색
        for(int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            
            if(!isRange(nr, nc)) continue; // 맵 밖이면 패스
            if(visited[nr][nc]) continue;     // 이미 간 곳 패스
            if(place[nr][nc] == 'X') continue; // 파티션이면 패스
            
            // 만약 거리가 2 이하인데 사람을 만난 경우
            if(place[nr][nc] == 'P') return false; 
            
            visited[nr][nc] = true;
            q.push({nr, nc, dist + 1});
        }
    }
    return true;
}

vector<int> solution(vector<vector<string>> places) {
    vector<int> answer;
    
    for(auto place : places) {
        bool ok = true;
        for(int i = 0; i < 5 && ok; i++) {
            for(int j = 0; j < 5 && ok; j++) {
                if(place[i][j] == 'P') {
                    // P를 발견할 때마다 BFS를
                    if(!bfs(i, j, place)) ok = false;
                }
            }
        }
        answer.push_back(ok ? 1 : 0);
    }
    return answer;
}