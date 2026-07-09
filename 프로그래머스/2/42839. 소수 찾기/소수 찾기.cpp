#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

unordered_set<int> us;
string Numbers;
vector<bool> visited;

bool isPrime(int n){
    if(n < 2) return false;
    for(int i = 2; i * i <= n; i++){
        if(n % i == 0) return false;
    }
    return true;
}

void backtrack(string num){
    if(!num.empty() && isPrime(stoi(num))){
        us.insert(stoi(num));
    }
    
    for(int i = 0; i < Numbers.size(); i++){
        if(visited[i]) continue;
        visited[i] = true;
        backtrack(num + Numbers[i]);
        visited[i] = false;
    }
}

int solution(string numbers) {
    Numbers = numbers;
    us.clear();
    visited.assign(Numbers.size(),false);
    backtrack("");
    return us.size();
}