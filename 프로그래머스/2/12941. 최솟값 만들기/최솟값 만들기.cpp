#include <iostream>
#include<vector>
#include <bits/stdc++.h>
using namespace std;

int solution(vector<int> A, vector<int> B)
{
    // 오름차순 배열
    sort(A.begin(), A.end());
    
    // 내림차순 배열
    sort(B.begin(), B.end(), greater<>());
    
    int result = 0;
    
    for(int i = 0; i < A.size(); i++){
        result += A[i] * B[i];
    }
    
    return result;
}