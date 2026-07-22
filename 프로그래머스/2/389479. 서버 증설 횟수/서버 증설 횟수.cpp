#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

int solution(vector<int> players, int m, int k) {
    // (7 - 1) 이라면 7초에 서버 1개를 빼야한다는 뜻
    unordered_map<int,int> server;
    int answer = 0;
    int server_cnt = 0;
    for(int i = 0; i < players.size(); i++){
        // 현재 사용중인 사람의 수
        int using_people = players[i];
        // 빼야하는 서버가 있다면 빼기
        if(server.count(i)){
            server_cnt -= server[i];
            server.erase(i);
        }
        // 증설 필요한 서버의 수
        int need_server = using_people / m - server_cnt;
        // 서버가 부족하다면 서버 증설
        if(need_server >= 1){
            server_cnt += need_server;
            answer += need_server;
            server[i + k] += need_server;
        }
    }
    
    return answer;
}