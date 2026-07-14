#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

bool canDivide(const vector<int>& arr, int num){
    bool divide = false;
    for(int a : arr){
        if(a % num == 0) return true;
    }
    
    return false;
}

int solution(vector<int> arrayA, vector<int> arrayB) {
    int gcd_a = arrayA[0];
    int gcd_b = arrayB[0];
    for(int i = 1; i < arrayA.size(); i++){
        gcd_a = gcd(gcd_a, arrayA[i]);
    }
    for(int i = 1; i < arrayB.size(); i++){
        gcd_b = gcd(gcd_b, arrayB[i]);
    }
    
    if(canDivide(arrayA, gcd_b)){
        gcd_b = 0;
    }
    if(canDivide(arrayB, gcd_a)){
        gcd_a = 0;
    }
    
    return max(gcd_a, gcd_b);
    
}