#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;


bool cmp(const vector<int>& v1, const vector<int>& v2){
    return v1[0] < v2[0];
}

int solution(vector<vector<int>> jobs) {
    int total_time = 0;
    // 소요시간, 요청시간 순
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    
    sort(jobs.begin(), jobs.end(), cmp); // 0,3 / 3,5 / 1,9 
    
    int n = jobs.size();
    int idx = 0;
    int cur_time = 0;
    
    while(idx < n || !pq.empty()){
        while(idx < n && jobs[idx][0] <= cur_time){
            pq.push({jobs[idx][1],jobs[idx][0]});
            idx++;
        }
        if(!pq.empty()){
            auto [elapsed_time, request_time] = pq.top();
            pq.pop();
            cur_time += elapsed_time;
            total_time += cur_time - request_time;
        }
        else{
            cur_time = jobs[idx][0];
        }
    }
    
    
    return total_time / n;

    
}