#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;


long long getMax(const vector<int>& arr){
    long long cur = arr[0];
    long long max_sum = arr[0];
    for(int i = 1 ; i < arr.size(); i++){
        long long num = arr[i];
        cur = max(num, cur + num);
        max_sum = max(max_sum, cur);
    }
    return max_sum;
}

long long solution(vector<int> sequence) {
    vector<int> sequence1(sequence.begin(), sequence.end()); // -1, 1 .. 곱한것
    vector<int> sequence2(sequence.begin(), sequence.end()); // 1, -1 .. 곱한것
    int n = sequence.size();
    
    for(int i = 0; i < n; i += 2){
        sequence1[i] = sequence1[i] * (-1);
    }
    for(int i = 1; i < n; i += 2){
        sequence2[i] = sequence2[i] * (-1);
    }
    
    return max(getMax(sequence1), getMax(sequence2));
    
}