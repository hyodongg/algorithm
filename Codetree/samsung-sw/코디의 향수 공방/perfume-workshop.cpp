#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
1: 향료 준비
2: 향료 추가
3: 향료 폐기 --
4: 블렌딩 --
5: 향수 구성 수행 --
*/

int N;
int n;
map<int,int> perfumes; // 향수 번호, 향도
vector<pair<int,int>> commands;
long long freq[3001]; // 향도가 idx 것의 개수

int current_max_id; // ** 오답노트 **

void init(){
    cin >> N;
    int x; cin >> x;
    cin >> n;
    current_max_id = n;

    for(int i = 1; i <= n; i++){
        int v;
        cin >> v;
        perfumes[i] = v;
        freq[v] += 1;
    }
    for(int i = 0; i < N - 1; i++){
        int first, second;
        cin >> first >> second;
        commands.push_back({first, second});
    }
}

// 2인 경우 향료 추가
void addPerfume(int v){
    // int next_key = perfumes.rbegin()->first + 1; **오답노트**
    current_max_id++;
    perfumes[current_max_id] = v;
    
    // freq 배열 반영
    freq[v] += 1;
}

// 3인 경우 향료 삭제
void removePerfume(int idx){
    // 존재 하지 않는 번호라면
    if(!perfumes.count(idx)) {
        cout << -1 << "\n";
    }
    else{
        int scent_degree = perfumes[idx];
        perfumes.erase(idx);
        cout << scent_degree << "\n";

        // freq 배열 반영, 어차피 count로 존재 확인해서 >0인지는 확인할 필요가 없지 않을까...
        freq[scent_degree] -= 1;
    }
}

// 4인 경우 향수 블렌딩 dp를 써라 향도 합이 정확히 K
void blending(int K){
    vector<int> dp(K + 1, 1e9); // 향도가 K가 되도록 선택할 때 필요한 향료의 최소개수
    dp[0] = 0;

    vector<int> available_scents;

    // 현재 사용가능한 향도 벡터
    for(auto [num, scent] : perfumes){
        available_scents.push_back(scent);
    }

    for(int i = 1; i <= K; i++){
        for(int j = 0; j < available_scents.size(); j++){
            int scent = available_scents[j];
            if(i - scent >= 0){
                dp[i] = min(dp[i], dp[i - scent] + 1);
            }
        }
    }
    if(dp[K] == 1e9) cout << -1 << "\n";
    else cout << dp[K] << "\n";
}

// 5인 경우 향수 구성 2개로 ..
// 탑 + 미들 >= K - 베이스
void makePerfume(int K){
    long long cnt = 0;
    long long top_middle[6001] = {0,};
    for(int i = 1; i < 3001; i++){
        for(int j = 1; j < 3001; j++)
            top_middle[i+j] += freq[i] * freq[j];
    }

    for(int i = 1; i < 6001; i++){
        for(int j = 1; j < 3001; j++){
            if(i + j >= K) cnt += top_middle[i] * freq[j];
        }
    }

    cout << cnt << "\n";
}

void debug(){
    for(auto [num, degree]: perfumes){
        cout << "(" << num << "," << degree << ")" << " ";
    }
    cout << "\n";
}

void debugCommands(){
    for(auto [a, b]: commands){
        cout << "(" << a << "," << b << ")" << " ";
    }
}


int main() {
    init();
    // debugCommands();
    for(int i = 0; i < commands.size(); i++){
        pair<int,int> command = commands[i];
        int num = command.first;
        int what = command.second;
        if(num == 2){
            //cout << "2번실행 ->";
            addPerfume(what);
        }
        else if(num == 3){
            //cout << "3번실행 ->";
            removePerfume(what);
            //debug();
        }
        else if(num == 4){
            //cout << "4번실행 ->";
            blending(what);
        }
        else if(num == 5){
            //cout << "5번실행 ->";
            makePerfume(what);
        }
    }
    // Please write your code here.
    return 0;
}