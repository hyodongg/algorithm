#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

string solution(string s) {
    string result = "";
    bool isFirst = true;
    for(char c : s){
        // 대문자로 바꾸기
        
        if(isFirst){
            if(isalpha(c)){
                result.push_back(toupper(c));
            }
            else result.push_back(c);
            
            isFirst = false;
        }
        else {
            if(isalpha(c)){
                result.push_back(tolower(c));
            }
            else result.push_back(c);
        }
        
        if(c == ' ') isFirst = true;
        else isFirst = false;
    }
    
    return result;
}