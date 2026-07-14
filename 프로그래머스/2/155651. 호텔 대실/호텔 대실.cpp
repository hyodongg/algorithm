#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

int getMinute(string s){
    return stoi(s.substr(0,2)) * 60  + stoi(s.substr(3,2));
}

// 입실 시간이 빠른 순으로 정렬
bool cmp(const vector<string>& s1, const vector<string>& s2){
    return getMinute(s1[0]) < getMinute(s2[0]);
}

int solution(vector<vector<string>> book_time) {
    // 정렬
    sort(book_time.begin(), book_time.end(), cmp);
    
    // 최소 힙
    priority_queue<int, vector<int>, greater<int>> pq;
    
    int cnt = 0;
    
    for(int i = 0; i < book_time.size(); i++){
        int start_time = getMinute(book_time[i][0]);
        int end_time = getMinute(book_time[i][1]);
        if(pq.empty()){
            pq.push(end_time);
            cnt++;
        }
        else{
            if(pq.top() + 10 <= start_time){
                pq.pop();
                pq.push(end_time);
            }
            else{
                pq.push(end_time);
                cnt++;
            }
        }
        
    }
    
    return cnt;
}