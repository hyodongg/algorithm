#include<iostream>

using namespace std;

int dr[4] = {1, -1 ,0, 0};
int dc[4] = {0, 0, -1, 1};

void solve(int tc){
   	int board[100][100];
    int answer = 0;
    
    // 사다리판 생성
    for(int i = 0; i < 100; i++){
        for(int j = 0; j < 100; j++){
            cin >> board[i][j];
        }
    }

    for(int i = 0; i < 100; i++){
        int start_c;
        int cur_r;
        int cur_c;
        start_c = i;

        if(board[0][i] == 1){
            cur_r = 0;
            cur_c = i;
        }
        else{
            continue;
        }
        
        while(cur_r < 99){
            if(cur_c > 0 && board[cur_r][cur_c - 1] == 1 ){
                while(board[cur_r][cur_c - 1] == 1 && cur_c > 0){
                	cur_c--;
            	}
            }
            else if(cur_c < 99 && board[cur_r][cur_c + 1] == 1){
                while(board[cur_r][cur_c + 1] == 1 && cur_c < 99){
                	cur_c++;
            	}
            }
            
            cur_r++;
        	}
        if (board[cur_r][cur_c] == 2) {
            answer = start_c;
            break; // 정답을 찾았으므로 탐색 종료
        }
    }
    cout << "#" << tc << " " << answer << "\n";
}

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int test_case;
    
    while (cin >> test_case) { 
        solve(test_case); // 입력받은 진짜 테스트케이스 번호를 그대로 넘겨줌
    }
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}