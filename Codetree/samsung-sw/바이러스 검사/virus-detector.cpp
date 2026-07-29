#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int main() {
    long long N;
    cin >> N;
    vector<long long> store(N+1);
    for(long long i = 1; i <= N; i++){
        cin >> store[i];
    }

    long long captain;
    cin >> captain;
    long long member;
    cin >> member;

    long long answer = 0;

    for(long long i = 1; i <= N; i++){
        store[i] -= captain;
        answer++;
        if(store[i] > 0){
        long long num = (store[i] - 1) / member + 1;
        answer += num;
        }
    }

    cout << answer << "\n";

    return 0;
}
