#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

bool cmp(int num1, int num2){
    string s1 = to_string(num1) + to_string(num2);
    string s2 = to_string(num2) + to_string(num1);
    return stoi(s1) > stoi(s2); // 큰 값이 앞으로
}

string solution(vector<int> numbers) {
    sort(numbers.begin(), numbers.end(), cmp);
    
    string answer = "";
    for(int n : numbers){
        answer += to_string(n);
    }
    
    if(answer[0] == '0') return "0";
    
    return answer;
}