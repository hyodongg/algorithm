#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

// n -> k 진수 변환
string toBase(int n, int k){
    string result = "";
    while(n > 0){
        int r = n % k;
        result += (r < 10 ? r + '0' : r - 10 + 'A');
        n = n / k;
    }
    reverse(result.begin(), result.end());
    return result;
}

bool isPrime(long long  num){
    if(num < 2) return false;
    for(long long  i = 2; i <= num / i; i++){
        if(num % i == 0) return false;
    }
    
    return true;
}

int solution(int n, int k) {
    int answer = 0;
    string num = toBase(n, k); // num = 211020101011
    
    string temp = "";
    for(int i = 0; i < num.size(); i++){
        if(num[i] == '0'){
            if(!temp.empty() && isPrime(stoll(temp))){
                answer++;
            }
            temp.clear();
        }
        else{
            temp += num[i];
        }
    }
    // 반복문 끝나고 마지막 문자 처리
    if(!temp.empty() && isPrime(stoll(temp))){
        answer++;
    }
    
    return answer;
}