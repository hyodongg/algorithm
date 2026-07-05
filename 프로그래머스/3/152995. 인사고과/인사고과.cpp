#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

bool cmp(const vector<int>& v1, const vector<int>& v2){
    if(v1[0] == v2[0]) {
        return v1[1] < v2[1]; // 근태 점수가 같으면 동료 평가 점수 오름차순
    }
    return v1[0] > v2[0]; // 근태 점수 내림차순
}

int solution(vector<vector<int>> scores) {
    
    // 원호의 점수 기록
    vector<int> target = scores[0];
    int target_total = target[0] + target[1];
    
    
    // 근태점수로 내림차순, 근태점수 같다면 동료점수로 오름차순
    sort(scores.begin(),scores.end(), cmp);
    
    vector<vector<int>> entry;
    
    bool is_target_alive = false;
    
    int max_peer_score = 0;
    for(int i = 0; i < scores.size(); i++){
        if(max_peer_score <= scores[i][1]) {
            entry.push_back(scores[i]);
            max_peer_score = max(max_peer_score, scores[i][1]);
            
            
            if(scores[i] == target) {
                is_target_alive = true;
            }
        }
        
        // 살아남은 사람 중에 완호가 있다면 flag true
        
    }
    
    if (!is_target_alive) {
        return -1;
    }
    
    
    int answer = 1;
    for(const auto& v : entry) {
        if(v[0] + v[1] > target_total) {
            answer++;
        }
    }
    
    return answer;
}