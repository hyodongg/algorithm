#include <iostream>
#include <string>
#include <map>

using namespace std;

void solve(int tc){
    int N;
    string S;
    cin >> N >> S;
    
    long long answer = 0; // 정답의 개수를 저장할 변수
    
    map<pair<int, int>, int> m;
    m[{0, 0}] = 1; // 시작 전 잔고 0인 상태를 기록
    
    int diff_AT = 0;
    int diff_GC = 0;
    
    for(int i = 0; i < S.size(); i++){
        if(S[i] == 'A') diff_AT++;
        else if(S[i] == 'T') diff_AT--;
        else if(S[i] == 'G') diff_GC++;
        else if(S[i] == 'C') diff_GC--;
        
        // 1. 구간을 만날 때마다 과거의 기록을 조회해서 answer에 누적
        answer += m[{diff_AT, diff_GC}];
        
        // 2. 현재 상태를 일기장에 기록
        m[{diff_AT, diff_GC}]++;
    }
    
    cout << answer << "\n";
}

int main(int argc, char** argv)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
	int T; // 
	if(cin >> T){
        for(int test_case = 1; test_case <= T; ++test_case){
            solve(test_case);
        }
    }
	return 0;
}