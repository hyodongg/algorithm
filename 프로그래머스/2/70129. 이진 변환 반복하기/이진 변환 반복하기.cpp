#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;


string toBase(int a, int b){ // a를 b진수로 변환
    string result = "";
    while(a != 0){
        int r = a % b;
        result += r < 10 ? r + '0' : r - 10 + 'A';
        a /= b;
    }
    reverse(result.begin(), result.end());
    
    return result;
    
}

vector<int> solution(string s) {
    int cnt = 0;
    int zero_cnt = 0;
    
    while(s != "1"){
        string temp = "";
        for(char c : s){
            if(c != '0'){
                temp += '1';
            }
            else {
                zero_cnt++;
            }
        }
        s = toBase(temp.size(), 2);
        cnt++;
    }
    
    return vector<int>{cnt, zero_cnt};
}