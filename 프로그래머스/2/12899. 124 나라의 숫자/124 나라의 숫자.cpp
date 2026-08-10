#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string solution(int n) {
    string answer = "";
    char num[3] = {'4', '1', '2'}; // 나머지가 0일때 '4', 1일때 '1', 2일때 '2'
    
    while(n > 0){
        int remainder = n % 3;
        answer += num[remainder];
        
        if(remainder == 0){
            // 딱 떨어지면(나머지가 0이면), 몫을 1 줄인다
            n = (n / 3) - 1; 
        } else {
            // 안 떨어지면 정상적으로 몫을 구한다.
            n = n / 3;
        }
    }
    
    reverse(answer.begin(), answer.end());
    return answer;
}