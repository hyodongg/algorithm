#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

// n을 k진수로 변환
string toBase(long long n, int k){
    string result = "";
    while(n > 0){
        long long r = n % k;
        result += (r < 10 ? r + '0': r - 10 + 'A');
        n /= k;
    }
    reverse(result.begin(), result.end());
    
    return result;
}

long long toDecimal(string s, int k){
    long long val;
    long long result = 0;
    for(char c : s){
        if(isdigit(c)) val = c - '0';
        else val = c - 'A' + 10;
        
        result = result * k + val;
    }
    
    return result;
}

vector<long long> solution(vector<long long> numbers) {
    vector<long long> answer;
    for(int i = 0; i < numbers.size(); i++){
        long long num = numbers[i];
        // 짝수일 경우 +1만 하면 정답이 됨
        if(num % 2 == 0){
            answer.push_back(num + 1);
        }
        // 홀수일 경우 오른쪽부터 처음 만나는 0을 1로 바꾸고 그 오른쪽을 0으로 바꾸기
        else{
            string temp = toBase(num, 2);
            temp = '0' + temp;
            long long idx = temp.size() - 1;
            
            while(true){
                if(temp[idx] == '0') {
                    temp[idx] = '1';
                    temp[idx + 1] = '0';
                    break;
                }
                idx--;
            }
            answer.push_back(toDecimal(temp, 2));
        }
    }
    return answer;
    
}