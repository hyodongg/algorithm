#include <string>
#include <vector>
#include <algorithm>

// 시간 복잡도
// data의 길이는 2500
// row_end ~ row_begin 최대는 2500
// 2500번 반복


using namespace std;

int Col;

// col번쨰 컬럼 값 기준 오름차순, 첫번째 값 기준 내림차순
bool cmp(vector<int> v1, vector<int> v2){
    if(v1[Col - 1] != v2[Col - 1]){
        return v1[Col - 1] < v2[Col - 1];
    }
    return v1[0] > v2[0];
}

int getS(vector<int> v, int r){
    int sum = 0;
    for(int num : v){
        sum += num % r;
    }
    
    return sum;
}

int solution(vector<vector<int>> data, int col, int row_begin, int row_end) {
    int answer = 0;
    Col = col;
    
    // 정렬
    sort(data.begin(), data.end(), cmp);
    
    for(int i = row_begin; i <= row_end; i++){
        vector<int> d = data[i - 1];
        int S = getS(d, i);
        answer = answer ^ S;
    }
    
    return answer;
}