#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <algorithm>
using namespace std;

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};
int N, T;
vector<vector<string>> food; // 신봉 음식
vector<vector<int>> mind; // 신앙심

void debugFood(){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cout << food[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "==============" << "\n";
}
void debugMind(){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cout << mind[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "==============" << "\n";
}

void breakfast(){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            mind[i][j]++;
        }
    }
}

 vector<vector<pair<int,int>>> makeGroup(const vector<vector<string>>& food, const vector<vector<int>>& mind){
    // 신봉음식 같은 그룹들의 모음
    vector<vector<pair<int,int>>> groups;
    vector<vector<bool>> visited(N, vector<bool>(N, false)); // 이미 그룹 생성 된 경우
    queue<pair<int,int>> q;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(!visited[i][j]){
                // 신봉 음식 같은 목록 (0,0) (0,1) (1,0) (1,1);
                vector<pair<int,int>> temp;
                temp.push_back({i,j});
                q.push({i,j});
                visited[i][j] = true;

                while(!q.empty()){
                    auto [cur_r, cur_c] = q.front();
                    q.pop();

                    for(int d = 0; d < 4; d++){
                        int nr = cur_r + dr[d];
                        int nc = cur_c + dc[d];
                        
                        if(nr < 0 || nr >= N || nc < 0 || nc >= N) continue;
                        if(visited[nr][nc]) continue;

                        // 신봉 음식이 같은 경우
                        if(food[cur_r][cur_c] == food[nr][nc]){
                            temp.push_back({nr,nc});
                            visited[nr][nc] = true;
                            q.push({nr,nc});
                        }
                    }
                }
                groups.push_back(temp);
            }
        }
    }
    return groups;
}

bool cmp(const pair<int,int>& p1, const pair<int,int>& p2){
    int r1 = p1.first; int c1 = p1.second;
    int r2 = p2.first; int c2 = p2.second;
    // 신앙심 큰 사람
    if(mind[r1][c1] != mind[r2][c2]){
        return mind[r1][c1] > mind[r2][c2];
    }
    else if(r1 != r2){
        return r1 < r2;
    }
    else return c1 < c2;
}

// 캡틴 정하고 신앙심 주고 받음
vector<vector<pair<int,int>>> chooseCaptain(vector<vector<pair<int,int>>>& groups){
    // 그룹마다
    for(int i = 0; i < groups.size(); i++){
        vector<pair<int,int>>& group = groups[i];
        // 대표자를 정하기 위한 정렬
        sort(group.begin(), group.end(), cmp);
        int people = group.size();
        int captain_r = group[0].first;
        int captain_c = group[0].second;
        mind[captain_r][captain_c] += people - 1;
        for(int j = 1; j < group.size(); j++){
            int person_r = group[j].first;
            int person_c = group[j].second;
            mind[person_r][person_c] -= 1;
        }
    }
    return groups;
}

void dinner(vector<vector<pair<int,int>>> sort_groups){
    // 대표자들 모음
    vector<pair<int,int>> captain;
    for(int i = 0; i < sort_groups.size(); i++){
        captain.push_back({sort_groups[i][0].first, sort_groups[i][0].second});
    }

    // 대표들을 그룹별로 나눠야함
    // !! 0: 단일 음식, 1: 이중 조합, 2: 삼중 조합 !!
    vector<vector<pair<int,int>>> captain_group(3);

    for(int i = 0; i < captain.size(); i++){
        int cur_r = captain[i].first;
        int cur_c = captain[i].second;
        captain_group[food[cur_r][cur_c].size() - 1].push_back({cur_r, cur_c});
    }
    
    // 그룹별로 나누고 전파할 순서 정함
    for(int i = 0; i < captain_group.size(); i++){
        sort(captain_group[i].begin(), captain_group[i].end(), cmp);
    }
    // 전파
    //전파 당한지 체크하기 위함
    vector<vector<bool>> visited(N, vector<bool>(N, false));
    for(int i = 0; i < captain_group.size(); i++){
        vector<pair<int,int>> captains = captain_group[i];
        for(int j = 0; j < captains.size(); j++){
            pair<int,int> captain = captains[j];
            int captain_r = captain.first;
            int captain_c = captain.second;
            if(visited[captain_r][captain_c]) continue;
            
            int x = mind[captain_r][captain_c] - 1;
            int dir = mind[captain_r][captain_c] % 4;  // 방향 정하기
            mind[captain_r][captain_c] = 1;


            if(x <= 0) continue; // 간절함이 0이면 애초에 시도 x !!!!!

            int nr = captain_r;
            int nc = captain_c;
            while(true){
                // 방향으로 한 칸 이동
                nr = nr + dr[dir];
                nc = nc + dc[dir];
                if(nr < 0 || nr >= N || nc < 0 || nc >= N) break;
                int y = mind[nr][nc];

                // 음식이 같을 때
                if(food[captain_r][captain_c] == food[nr][nc]) continue;
                // 강한 전파
                else if(x > y){
                    food[nr][nc] = food[captain_r][captain_c];
                    x = x - (y + 1);
                    mind[nr][nc] += 1;
                    
                    visited[nr][nc] = true;

                    if(x == 0) break;
                }
                // 약한 전파
                else if(x <= y){
                    // 음식 관심
                    unordered_set<string> us;
                    for(int k = 0; k < food[captain_r][captain_c].size(); k++){
                        us.insert(string(1, food[captain_r][captain_c][k]));
                    }
                    for(int k = 0; k < food[nr][nc].size(); k++){
                        us.insert(string(1, food[nr][nc][k]));
                    }
                    
                    if(us.count("T") && us.count("C") && us.count("M")){
                        food[nr][nc] = "TCM";
                    }
                    else if(us.count("C") && us.count("M")){
                        food[nr][nc] = "CM";
                    }
                    else if(us.count("T") && us.count("M")){
                        food[nr][nc] = "TM";
                    }
                    else if(us.count("T") && us.count("C")){
                        food[nr][nc] = "TC";
                    }
                    else if(us.count("T")){
                        food[nr][nc] = "T";
                    }
                    else if(us.count("C")){
                        food[nr][nc] = "C";
                    }
                    else if(us.count("M")){
                        food[nr][nc] = "M";
                    }
                    
                    // 전파가 간절함 0, 신앙심 x증가
                    mind[nr][nc] += x;
                    x = 0;
                    visited[nr][nc] = true;
                    break;
                }

            }
        }
    }
}

void lunchAndDinner(){
    vector<vector<pair<int,int>>> groups = makeGroup(food, mind);
    // 각 그룹의 맨 앞이 대표자인 배열
    vector<vector<pair<int,int>>> sort_groups = chooseCaptain(groups);

    dinner(sort_groups);
}

void init(){
    food.assign(N, vector<string>(N, ""));
    mind.assign(N, vector<int>(N,0));
    for(int i = 0; i < N; i++){
        string row;
        cin >> row;
        for(int j = 0; j < N; j++){
            food[i][j] = row[j];
        }
    }
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cin >> mind[i][j];
        }
    }
}

void getSum(){
    unordered_map<string, int> um;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            string s = food[i][j];
            um[s] += mind[i][j];
        }
    }
    cout << um["TCM"] << " " << um["TC"] << " " << um["TM"] 
    << " " << um["CM"] << " " << um["M"] << " " << um["C"] 
    << " " << um["T"] << " " << "\n";
}

int main() {
    cin >> N >> T;
    init();
    // debugFood();
    // debugMind();
    for(int i = 0; i < T; i++){
        breakfast();
        lunchAndDinner();
        getSum();
        // debugMind();
    }

    return 0;
}