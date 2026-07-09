#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

int solution(int N, vector<vector<int>> road, int K) {
    
    // pq: {누적 비용, 현재 노드}
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    // (현재 노드 - {다음노드, 간선비용})
    vector<vector<pair<int,int>>> graph(N + 1);
    
    vector<int> dist(N + 1,1e9);
    
    // 그래프 구성
    for(vector<int> r : road){
        int start = r[0];
        int end = r[1];
        int cost = r[2];
        graph[start].push_back({end, cost});
        graph[end].push_back({start, cost});
    }
    
    pq.push({0,1});
    dist[1] = 0;
    
    while(!pq.empty()){
        auto [cur_cost, cur_node] = pq.top();
        pq.pop();
        
        // 오래된 값 가지치기
        if(cur_cost > dist[cur_node]) continue;
        
        for(auto [next_node, edge_cost] : graph[cur_node]){
            
            // 새로운 후보 비용 = 지금까지의 비용 + 간선 비용
            int new_cost = cur_cost + edge_cost;
            
            // 더 짧은 경로 발견 시 갱신
            if(new_cost < dist[next_node]){
                dist[next_node] = new_cost;
                pq.push({new_cost, next_node});
            }
        }
    }
    
    int answer = 0;
    for(int i = 1; i < dist.size(); i++){
        if(dist[i] <= K) answer++;
    }
    
    return answer;
}