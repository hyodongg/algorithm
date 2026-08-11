#include <string>
#include <vector>

using namespace std;

long long fact(long long n){
    long long result = 1;
    for(long long i = 1; i <= n; i++){
        result *= i;
    }
    return result;
}

vector<int> solution(int n, long long k) {
    vector<int> nums(n);
    // nums = {1, 2, 3, 4, 5}
    for(int i = 0; i < n; i++){
        nums[i] = i + 1;
    }
    
    k-=1;
    
    vector<int> answer;
    while(!nums.empty()){
        int size = nums.size();
        long long q = k / fact(size - 1);
        long long r = k % fact(size - 1);
        
        answer.push_back(nums[q]);
        nums.erase(nums.begin() + q);
        
        k = r;
        
    }

    return answer;
}