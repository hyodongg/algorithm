#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

int dfs(int cur, const vector<vector<int>>& graph, int n, vector<bool>& visited){
    int node_cnt = 1;
    
    visited[cur] = true;
    
    for(int next_node : graph[cur]){
        if(visited[next_node]) continue;
        node_cnt += dfs(next_node, graph, n, visited);
    }
    return node_cnt;
}

int solution(int n, vector<vector<int>> wires) {
    
    int mn = 1e9;
    
    int idx = 0;
    
    // 하나씩 끊어보며 그래프 구성
    for(int i = 0; i < wires.size(); i++){
        vector<vector<int>> graph(n + 1);
        
        for(int j = 0; j < wires.size(); j++){
            if(idx == j) continue;
            int start = wires[j][0];
            int end = wires[j][1];
            graph[start].push_back(end);
            graph[end].push_back(start);
        }
        
        vector<bool> visited(n + 1, false);
        
        int node_cnt = dfs(1, graph, n, visited);
        mn = min(mn, abs(node_cnt - (n - node_cnt)));
        idx++;
        
    }
    
    return mn;
}