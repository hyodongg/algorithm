#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

// 100, -, 2--, *, 300, -, 500, +, 20
vector<string> calc(vector<string> v, char op){
    vector<string> next;

    for(int i = 0; i < v.size(); i++){
        if(v[i] == string(1, op)){
            long long a = stoll(next.back());
            long long b = stoll(v[i+1]);

            next.pop_back();

            long long res;
            if(op == '*') res = a * b;
            else if(op == '+') res = a + b;
            else res = a - b;

            next.push_back(to_string(res));
            i++; // 다음 숫자 skip
        }
        else{
            next.push_back(v[i]);
        }
    }

    return next;
}

long long solution(string expression) {
    vector<string> v;

    string temp = "";
    for(char c : expression){
        if(c == '-' || c == '+' || c == '*'){
            v.push_back(temp);
            v.push_back(string(1, c));
            temp = "";
        }
        else{
            temp += c;
        }
    }
    v.push_back(temp);

    vector<vector<char>> orders = {
        {'*','+','-'},
        {'*','-','+'},
        {'+','*','-'},
        {'+','-','*'},
        {'-','*','+'},
        {'-','+','*'}
    };

    long long answer = 0;

    for(auto order : orders){
        vector<string> cur = v;

        for(char op : order){
            cur = calc(cur, op);
        }

        answer = max(answer, abs(stoll(cur[0])));
    }

    return answer;
}