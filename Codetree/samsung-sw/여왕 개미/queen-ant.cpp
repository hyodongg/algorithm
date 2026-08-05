#include <iostream>
#include <vector>
#include <map>
using namespace std;

vector<pair<int,int>> commands;
map<int,long long> houses; // 집 번호, 집 좌표
int Q;
int max_num; // 개미집 번호 최댓값

// 처음 마을 건설 및 명령어 넣기
void init(){
    cin >> Q;
    int N; cin >> N; // 처음 100은 필요없음
    int n; // 건설할 집 개수
    cin >> n;
    max_num = n;
    houses[0] = 0;
    for(int i = 1; i <= n; i++){
        int pos;
        cin >> pos;
        houses[i] = pos;
    }
    for(int i = 0; i < Q - 1; i++){
        int order, num;
        cin >> order >> num;
        commands.push_back({order,num});
    }
}

// 개미집 건설
void makeHouse(int pos){
    max_num++;
    houses[max_num] = pos;
}

// 개미집 철거
void destroyHouse(int num){
    houses.erase(num);
}

bool check(long long mid, int r){
    int ant_count = 0;
    long long cover_limit = -1;
    
    for(const auto& [id, pos] : houses){
        if(id == 0) continue;

        if(ant_count == 0 || pos > cover_limit){
            ant_count++;
            cover_limit = pos + mid;
        }
    }

    return ant_count <= r;
}

// 개미집 정찰 (r마리의 일개미가 정찰)
void seeHouse(int r){
    // 만약 살아있는 집이 여왕개미(0번) 하나뿐이거나 없다면 시간은 0
    if(houses.size() <= 1) {
        cout << 0 << "\n";
        return;
    }
    // time을 제일 크게 설정
    long long left = 0;
    long long right = houses.rbegin()->second - (++houses.begin())->second;
    long long ans = right;
    while(left <= right){
        long long mid = (left + right) / 2;

        if(check(mid, r)){ // mid초 동안 r마리의 개미로 모든 집을 정찰할 수 있는가?
            ans = mid;
            right = mid - 1;
        }
        else{
            left = mid + 1;
        }
    }
    cout << ans << "\n";
}

int main() {
    init();
    for(int i = 0; i < Q - 1; i++){
        pair<int,int> command = commands[i];
        // 건설 명령
        if(command.first == 200){
            makeHouse(command.second);
        }
        // 철거 명럴
        else if(command.first == 300){
            destroyHouse(command.second);
        }
        // 정찰 명령
        else if(command.first == 400){
            seeHouse(command.second);
        }
    }
    return 0;
}