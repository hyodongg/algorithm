#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

int solution(vector<int> people, int limit) {
    // 오름차순 정렬
    sort(people.begin(), people.end());
    int left = 0;
    int right = people.size() - 1;
    int answer = 0;
    
    while(left <= right){ // 등호?
        int sum = people[left] + people[right];
        if(sum <= limit){
            answer += 1;
            left++;
            right--;
        }
        else{
            answer += 1;
            right--;
        }
        
    }
    return answer;
    
    
}