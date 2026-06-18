# C++ STL 및 필수 알고리즘 정리

## 1. 기본 컨테이너

### vector
- 선언: `vector<int> v;`
- 초기화: `vector<int> v(n, 0);`
- 주요 메서드:
  - `v.push_back(x)`
  - `v.pop_back()`
  - `v.size()`
  - `v.empty()`
  - `v.clear()`
  - `v.resize(n)`
  - `v.begin(), v.end()`
  - `v[i]`

### deque
- 양쪽 삽입/삭제 가능
- `dq.push_front(x), dq.push_back(x)`
- `dq.pop_front(), dq.pop_back()`

### stack
- `stack<int> s;`
- `s.push(x)`
- `s.pop()`
- `s.top()`
- `s.empty()`

### queue
- `queue<int> q;`
- `q.push(x)`
- `q.pop()`
- `q.front()`
- `q.back()`

### priority_queue (힙)
- 최대 힙: `priority_queue<int> pq;`
- 최소 힙: `priority_queue<int, vector<int>, greater<int>> pq;`
- `pq.push(x)`
- `pq.pop()`
- `pq.top()`

---

## 2. 정렬 및 탐색

### sort
```cpp
sort(v.begin(), v.end()); // 오름차순
sort(v.begin(), v.end(), greater<int>()); // 내림차순
```

### custom sort
```cpp
bool cmp(int a, int b) {
    return a > b;
}
sort(v.begin(), v.end(), cmp);
```

### binary_search
```cpp
binary_search(v.begin(), v.end(), x);
```

### lower_bound / upper_bound
```cpp
lower_bound(v.begin(), v.end(), x); // 이상
upper_bound(v.begin(), v.end(), x); // 초과
```

---

## 3. map / set

### map
- key-value 저장 (정렬됨)
```cpp
map<string, int> m;
m["a"] = 1;
m.insert({"b", 2});
m.erase("a");
m.find("b");
```

### unordered_map
- 해시 기반 (빠름)
```cpp
unordered_map<int, int> um;
```

### set
```cpp
set<int> s;
s.insert(x);
s.erase(x);
s.count(x);
```

### unordered_set
```cpp
unordered_set<int> us;
```

---

## 4. 문자열 (string)

### 기본
```cpp
string s = "hello";
```

### 주요 메서드
- `s.size()`
- `s.empty()`
- `s.substr(pos, len)`
- `s.find("abc")`
- `s.erase(pos, len)`
- `s.insert(pos, str)`
- `s.push_back(c)`
- `s.pop_back()`
- `reverse(s.begin(), s.end())`

### 문자열 → 숫자
```cpp
stoi(s)
stol(s)
stoll(s)
stod(s)
```

### 숫자 → 문자열
```cpp
to_string(x)
```

---

## 5. pair / tuple

### pair
```cpp
pair<int, int> p = {1, 2};
p.first;
p.second;
```

### tuple
```cpp
tuple<int, int, int> t = {1, 2, 3};
get<0>(t);
```

---

## 6. 기타 유용한 함수

### swap
```cpp
swap(a, b);
```

### min / max
```cpp
min(a, b);
max(a, b);
```

### accumulate
```cpp
#include <numeric>
accumulate(v.begin(), v.end(), 0);
```

### count
```cpp
count(v.begin(), v.end(), x);
```

### find
```cpp
find(v.begin(), v.end(), x);
```

---

## 7. 순열 / 조합

### next_permutation
```cpp
sort(v.begin(), v.end());
do {
    // 처리
} while(next_permutation(v.begin(), v.end()));
```

### prev_permutation
```cpp
prev_permutation(v.begin(), v.end());
```

---

## 8. 그래프 기본 템플릿

### DFS
```cpp
void dfs(int x) {
    visited[x] = true;
    for (int nx : adj[x]) {
        if (!visited[nx]) dfs(nx);
    }
}
```

### BFS
```cpp
queue<int> q;
q.push(start);
visited[start] = true;

while (!q.empty()) {
    int x = q.front(); q.pop();
    for (int nx : adj[x]) {
        if (!visited[nx]) {
            visited[nx] = true;
            q.push(nx);
        }
    }
}
```

---

## 9. DP 기본 패턴

### 1차원 DP
```cpp
for (int i = 1; i <= n; i++) {
    dp[i] = dp[i-1] + ...;
}
```

### 2차원 DP
```cpp
for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
        dp[i][j] = ...;
    }
}
```

---

## 10. 입출력 최적화

```cpp
ios::sync_with_stdio(false);
cin.tie(NULL);
```

---

## 11. 자주 쓰는 자료형

```cpp
typedef long long ll;
typedef pair<int,int> pii;
```

---

## 12. 범위 기반 for문

```cpp
for (auto x : v) {}
for (auto &x : v) {}
```

---

## 13. 람다 함수

```cpp
auto f = [](int a, int b) {
    return a + b;
};
```

---

