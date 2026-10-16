#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

vector<string> Words;

// 단어가 하나만 다른지 판별 -> 바꿀 수 있는가
bool canChange(string cur_word, string next_word){
    int cnt = 0;
    for(int i = 0 ; i < cur_word.size(); i++){
        if(cur_word[i] != next_word[i]) cnt++;
    }
    if(cnt == 1) return true;
    return false;
}

int solution(string begin, string target, vector<string> words) {
    Words = words;
    bool can = false;
    for(string w : Words){
        if(w == target) can = true;
    }
    if(!can) return 0;
    
    // 현재 단어, 변환횟수
    queue<pair<string, int>> q;
    q.push({begin, 0});
    while(!q.empty()){
        auto [cur_word, cnt] = q.front();
        // cout << cur_word << " " << cnt << endl;
        q.pop();
        
        // 목표 도달하면 바로 반환
        if(cur_word == target) return cnt;
        
        for(string w : Words){
            if(canChange(cur_word, w)){
                q.push({w, cnt + 1});
            }
        }
    }
    
    return 0;
    
}