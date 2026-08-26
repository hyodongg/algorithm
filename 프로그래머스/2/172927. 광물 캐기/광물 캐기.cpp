#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

struct Mineral{
    int dia = 0;
    int iron = 0;
    int stone = 0;
};

bool cmp(Mineral m1, Mineral m2){
    if(m1.dia != m2.dia) return m1.dia > m2.dia;
    else if(m1.iron != m2.iron) return m1.iron > m2.iron;
    else return m1.stone > m2.stone;
}

int solution(vector<int> picks, vector<string> minerals) {
    int length = min((accumulate(picks.begin(), picks.end(), 0) * 5), (int)minerals.size());
    
    vector<Mineral> v;
    
    for(int i = 0; i < length; i += 5){
        Mineral m;
        for(int j = i; j < i + 5 && j < length; j++){
            if(minerals[j] == "diamond"){
                m.dia += 1;
            }
            if(minerals[j] == "iron"){
                m.iron += 1;
            }
            if(minerals[j] == "stone"){
                m.stone += 1;
            }
        }
        // Mineral완성 후 vector에 넣기
        v.push_back(m);
    }
    // 다이아 많은 순으로 정렬
    sort(v.begin(), v.end(), cmp);
    
    int answer = 0;
    
    for(int i = 0; i < v.size(); i++){
        if(picks[0] > 0){
            picks[0]--;
            answer += v[i].dia * 1 + v[i].iron * 1 + v[i].stone * 1;
        }
        else if(picks[1] > 0){
            picks[1]--;
            answer += v[i].dia * 5 + v[i].iron * 1 + v[i].stone * 1;
        }
        else if(picks[2] > 0){
            picks[2]--;
            answer += v[i].dia * 25 + v[i].iron * 5 + v[i].stone * 1;
        }
    }
    
    return answer;
    
}