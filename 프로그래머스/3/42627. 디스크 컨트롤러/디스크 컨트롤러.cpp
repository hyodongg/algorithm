#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool cmp(pair<int,int> p1, pair<int,int> p2){
    int a = p1.second - p1.first;
    int b = p2.second - p2.first;
    if(a == b) return p1.first < p2.first;
    else return a < b;
}

vector<int> solution(vector<int> sequence, int k) {
    vector<pair<int,int>> result;
    int length = sequence.size();
    int left_idx = 0;
    int right_idx = 0;
    int sum = sequence[0];
    while(left_idx < length){
        if(sum == k){
            result.push_back({left_idx, right_idx});
            sum -= sequence[left_idx];
            left_idx++;
        }
        else if(sum < k){
            if(right_idx == length - 1) break; // right가 끝에 도달
            right_idx++;
            sum += sequence[right_idx];
        }
        else if(sum > k){
            sum -= sequence[left_idx];
            left_idx++;
        }
    }
    if(result.size() == 1) return vector<int>{result[0].first, result[0].second};
    
    sort(result.begin(), result.end(), cmp); // 길이가 짧은게 앞으로 오도록
    
    return vector<int>{result[0].first, result[0].second};
}
