#include <string>
#include <vector>
#include <bits/stdc++.h>


using namespace std;

int solution(vector<string> want, vector<int> number, vector<string> discount) {
    unordered_map<string,int> wanted_map;
    // wanted_map구성
    for(int i = 0; i < number.size(); i++){
        wanted_map[want[i]] = number[i];
    }
    
    int answer = 0;
    
    
    for(int i = 0; i + 9 < discount.size(); i++){
        unordered_map<string,int> temp = wanted_map;
        
        for(int k = i; k < i + 10; k++){
            if(temp[discount[k]] > 0){
                temp[discount[k]]--;
                if(temp[discount[k]] == 0){
                temp.erase(discount[k]);
                }
            }  
            if(temp.empty()) {
                answer++;
            }
        }
    }
    return answer;
    
    
}