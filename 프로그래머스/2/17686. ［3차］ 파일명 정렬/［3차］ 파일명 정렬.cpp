#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

struct File{
    string HEAD;
    string NUMBER;
    string TAIL;
    int origin_idx;
};

bool cmp(const File& f1,const File& f2){
    string head1 = "";
    string head2 = "";
    for(char c : f1.HEAD){
        head1 += tolower(c);
    }
    for(char c : f2.HEAD){
        head2 += tolower(c);
    }
    int num1 = stoi(f1.NUMBER);
    int num2 = stoi(f2.NUMBER);
    
    if(head1 == head2 && num1 == num2) return f1.origin_idx < f2.origin_idx;
    else if(head1 == head2) return num1 < num2;
    else return head1 < head2;
    
}

vector<string> solution(vector<string> files) {
    vector<File> v;
    int origin_idx = 0;
    for(string f : files){
        int idx = 0;
        string head = "";
        string number = "";
        string tail = "";
        while(idx < f.size() && !isdigit(f[idx])){
            head += f[idx];
            idx++;
        }
        while(idx < f.size() && isdigit(f[idx])){
            number += f[idx];
            idx++;
        }
        while(idx < f.size()){
            tail += f[idx];
            idx++;
        }
        
        v.push_back({head, number, tail, origin_idx});
        origin_idx++;
    }
    
    sort(v.begin(), v.end(), cmp);
    
    vector<string> answer;
    
    for(const auto& file : v){
        answer.push_back(file.HEAD + file.NUMBER + file.TAIL);
    }
    
    return answer;
}