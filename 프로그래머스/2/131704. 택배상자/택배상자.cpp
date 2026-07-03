#include <string>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

int solution(vector<int> order) {
    queue<int> main_belt; // 기존 컨테이너 벨트 (선입선출)
    stack<int> sub_belt;  // 보조 컨테이너 벨트 (후입선출)
    
    int answer = 0;
    int idx = 0; // 현재 실어야 할 order 배열의 인덱스 (타겟 상자 위치)
    
    // 1. 메인 벨트에 1번부터 N번 상자까지 올림
    for(int i = 1; i <= order.size(); i++){
        main_belt.push(i);
    }
    
    // 2. 무한 루프를 돌며 상자를 찾습니다.
    while (idx < order.size()) {
        int target = order[idx]; // 지금 트럭에 실어야 하는 상자 번호
        
        // 1순위: 보조 벨트 맨 위가 타겟인 경우
        if (!sub_belt.empty() && sub_belt.top() == target) {
            sub_belt.pop();
            answer++;
            idx++; // 다음 타겟으로 넘어감
        }
        // 2순위: 메인 벨트 맨 앞이 타겟인 경우
        else if (!main_belt.empty() && main_belt.front() == target) {
            main_belt.pop();
            answer++;
            idx++; // 다음 타겟으로 넘어감
        }
        // 3순위: 둘 다 타겟이 아니면, 메인 벨트의 상자를 보조 벨트로 옮긴다.
        else if (!main_belt.empty()) {
            sub_belt.push(main_belt.front());
            main_belt.pop();
        }
        // 4순위: 둘 다 타겟도 아니고, 메인 벨트에서 더 이상 가져올 상자도 없다면 끝
        else {
            break; 
        }
    }
    
    return answer;
}