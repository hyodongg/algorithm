#include <string>
#include <vector>

using namespace std;

int answer;
vector<int> number;
int target_num;

void dfs(int idx, int sum){
    if(idx == number.size()){
        if(sum == target_num){
            answer++;
        }
        return;
    }
    dfs(idx + 1, sum + number[idx]);
    dfs(idx + 1, sum - number[idx]);
}

int solution(vector<int> numbers, int target) {
    answer = 0;
    number = numbers;
    target_num = target;
    dfs(0, 0);
    return answer;
}

