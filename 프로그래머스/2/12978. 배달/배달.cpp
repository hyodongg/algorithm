#include <iostream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

int solution(int N, vector<vector<int> > road, int K) {
    vector<vector<pair<int,int>>> graph(N + 1);
    // 무방향 그래프 현재노드 - {다음노드, 간선비용}
    for(vector<int> r : road){
        int start = r[0];
        int end = r[1];
        int cost = r[2];
        graph[start].push_back({end, cost});
        graph[end].push_back({start,cost});
    }
    // 최단거리 - 현재 노드
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    // 목표까지의 거리.
    vector<int> dist(N + 1, 1e9);
    
    pq.push({0, 1});
    dist[1] = 0;
    while(!pq.empty()){
        auto [cur_cost, cur_node] = pq.top();
        pq.pop();
        
        // 가지치기
        if(cur_cost > dist[cur_node]) continue;
        
        for(auto [next_node, edge_cost] : graph[cur_node]){
            int new_cost = cur_cost + edge_cost;
            
            if(new_cost < dist[next_node]){
                dist[next_node] = new_cost;
                pq.push({new_cost, next_node});
            }
            
        }
    }
    
    int answer = 0;
    for(int d : dist){
        if(d <= K){
            answer++;
        }
    }
    return answer;
}