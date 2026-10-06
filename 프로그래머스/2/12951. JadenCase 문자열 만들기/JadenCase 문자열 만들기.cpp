#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

string solution(string s) {
    string result = "";
    bool isFirst = true;
    for(char c : s){
        
        if(isFirst){
            result.push_back(toupper(c));

        }
        else {
            result.push_back(tolower(c));
        }
        
        if(c == ' ') isFirst = true;
        else isFirst = false;
    }
    
    return result;
}