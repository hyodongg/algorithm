#include<string>
#include <iostream>
#include <stack>

using namespace std;

bool solution(string s)
{
    stack<char> st;
    
    for(int i = 0; i < s.size(); i++){
        char c = s[i];
        // 여는 괄호라면 스택에 넣기
        if(c == '('){
            st.push(c);
        }
        // 닫힌 괄호라면
        else{
            if(st.empty()) return false;
            st.pop();
        }
    }
    if(st.empty()) return true;
    else return false;
}