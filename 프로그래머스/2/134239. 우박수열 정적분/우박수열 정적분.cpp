#include <string>
#include <vector>

using namespace std;

// 사다리꼴 넓이
double area(int a, int b){
    return (double(a) + double(b)) / 2;
}

vector<double> solution(int k, vector<vector<int>> ranges) {
    vector<pair<int,int>> v;
    int idx = 0;
    
    // k가 1이 되는 곳 찾기
    while(k > 1){
        v.push_back({idx, k});
        if(k % 2 == 0) k /= 2;
        else k = k * 3 + 1;
        idx++;
    }
    v.push_back({idx, k});
    
    vector<double> prefix_areas;
    prefix_areas.push_back(0.0);
    
    for(int i = 0; i < v.size() - 1; i++){
        double current_area = area(v[i].second, v[i+1].second);
        // 이전까지의 누적합에 현재 넓이를 더해서 저장
        prefix_areas.push_back(prefix_areas.back() + current_area);
    }
    
    vector<double> answer;
    
    // 정적분 구하기
    for(int i = 0; i < ranges.size(); i++){
        int x1 = ranges[i][0];
        int x2 = idx + ranges[i][1];
        
        if(x1 == x2) answer.push_back(0.0);
        else if(x1 < x2){
            // 누적 합을 활용하여 O(1) 만에 구간 합 구하기
            answer.push_back(prefix_areas[x2] - prefix_areas[x1]);
        }
        else{
            answer.push_back(-1.0);
        }
    }
    
    return answer;
}