#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

int solution(int storey) {
    
    int answer = 0;
    
    while(storey > 0){
        int num = storey % 10;
        // 5보다 큰 경우 -> 무조건 올림
        if(num > 5){
            answer += 10 - num;
            storey /= 10;
            storey += 1;
        }
        // 5인 경우 ->  그 앞자리가 5 이상이면 올리기, 아니면 내림
        else if(num == 5){
            if((storey / 10) % 10 >= 5){
                answer += 10 - num;
                storey /= 10;
                storey += 1;
            }
            else{
                answer += num;
                storey /= 10;
            }
        }
        // 5보다 작은 경우 -> 버림
        else if(num < 5){
            answer += num;
            storey /= 10;
        }
    }
    return answer;
}

