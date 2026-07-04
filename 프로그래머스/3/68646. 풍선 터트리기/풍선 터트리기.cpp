#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

int solution(vector<int> a) {
    int n = a.size();
    int answer = n;
    
    vector<int> left_min(n), right_min(n);
    
    left_min[0] = a[0];
    for(int i = 1; i < n; i++) left_min[i] = min(left_min[i-1], a[i]);
    
    right_min[n - 1] = a[n - 1];
    for(int i = n - 2; i >= 0; i--) right_min[i] = min(right_min[i + 1], a[i]);
    
    
    for(int i = 1; i < a.size() - 1; i++){
        if(left_min[i - 1] < a[i] && right_min[i + 1] < a[i]) answer--;
    }
    
    return answer;
}