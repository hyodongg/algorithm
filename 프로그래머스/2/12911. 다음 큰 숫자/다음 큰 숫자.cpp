#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

string toBase(int n, int k){
    string result = "";
    while(n > 0){
        int r = n % k;
        result += r < 10 ? r + '0' : r - 10 + 'A';
        n /= k;
    }
    
    reverse(result.begin(), result.end());
    
    return result;
}

int getOneCnt(string s){
    int one_cnt = 0;
    for(char c : s){
        if(c == '1') one_cnt++;
    }
    
    return one_cnt;
}

int solution(int n) {
    int next_num = n + 1;
    int n_one_cnt = getOneCnt(toBase(n, 2));
    while(n <= 1000000){
        if(n_one_cnt == getOneCnt(toBase(next_num, 2))){
            return next_num;
        }
        else next_num++;
    }
    
    return 0;
}
