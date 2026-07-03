#include <vector>
#include <queue>

using namespace std;

int solution(int x, int y, int n) {
    // x와 y가 같으면 시작하자마자 0 반환
    if (x == y) return 0;
    
    vector<int> dist(y + 1, -1);
    queue<int> q;
    
    q.push(x);
    dist[x] = 0;
    
    while(!q.empty()){
        int cur = q.front();
        q.pop(); // 큐에서 빼는 위치는 보통 맨 앞쪽으로 빼두는 것이 안전하고 깔끔함.
        
        vector<int> v = {cur + n, cur * 2, cur * 3};
        
        for(int next : v){
            if(next > y) continue;         // 범위를 벗어났는지 먼저 확인
            if(dist[next] != -1) continue; // 범위 안이라면, 방문했는지 확인
            
            // 정답을 찾았다면 큐에 넣을 필요 없이 바로 횟수 반환
            if(next == y) return dist[cur] + 1;
            
            q.push(next);
            dist[next] = dist[cur] + 1;
        }
    }
    
    return -1;
}