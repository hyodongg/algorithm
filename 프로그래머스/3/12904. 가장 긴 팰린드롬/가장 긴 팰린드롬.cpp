#include <iostream>
#include <string>
#include <bits/stdc++.h>
using namespace std;

int getLength(const string& s, int left, int right){
    while(left >= 0 && right < s.size() && s[left] == s[right]){
        left--;
        right++;
    }
    return right - left - 1;
}

int solution(string s)
{

    int mx = 1;
    
    for(int i = 0; i < s.size(); i++){
        int len1 = getLength(s, i, i);
        int len2 = getLength(s, i, i + 1);
        
        mx = max({mx, len1, len2});
    }
    return mx;
}