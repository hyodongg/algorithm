#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

vector<int> solution(vector<int> sequence, int k) {
    int left = 0, right = 0;
    int ans_left = 0, ans_right = 0;
    int num = 0;
    int length = 1e9;
    while(right < sequence.size()){
        num += sequence[right];
        
        while(left <= right && num >= k){
            if(num == k){
                if(length > right - left + 1){
                    length = right - left + 1;
                    ans_left = left;
                    ans_right = right;
                }
            }
            
            num -= sequence[left];
            left++;
        }
        right++;
    }
    
    return vector<int>{ans_left , ans_right};
}

// left , right 가 0으로 시작하는 투 포인터
// 길이가 짧은 수열 -> 시작 인덱스가 작은 수열