#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

string solution(string s) {
    vector<int> v;
    stringstream ss(s);
    int num;
    while(ss >> num){
        v.push_back(num);
    }
    
    return to_string(*min_element(v.begin(),v.end())) + " " + to_string(*max_element(v.begin(), v.end()));
}