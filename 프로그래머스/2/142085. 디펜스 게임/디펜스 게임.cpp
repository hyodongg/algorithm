#include <vector>
#include <queue> // 큐 헤더 추가

using namespace std;

int solution(int n, int k, vector<int> enemy) {
    priority_queue<int> pq; 
    
    for(int i = 0; i < enemy.size(); i++) {
        // 과거든 현재든 가리지 않고, 일단 싸우고 모두 기록
        n -= enemy[i];
        pq.push(enemy[i]);
        
        // 싸운 뒤 병사가 부족하다면 (후 수습)
        if(n < 0) {
            // 무적권이 남아있다면, 제일 컸던 전투(현재 전투 포함)를 환불
            if(k > 0) {
                n += pq.top(); 
                pq.pop();      
                k--;           
            }
            // 무적권도 없는데 병사가 부족하다면 끝
            else {
                return i; // i번째 라운드에서 죽었으니, 클리어한 라운드 수는 i개
            }
        }
    }
    
    // for문을 중간에 죽지 않고 무사히 다 돌았다면 전부 다 클리어한 것
    return enemy.size();
}