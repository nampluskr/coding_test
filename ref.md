# Reference Codes

## 자료구조 (구조체)

- [링크드 리스트 (Linked List)](https://github.com/nampluskr/coding_test/blob/main/ref/linked_list.md)
- [큐 (Queue)](https://github.com/nampluskr/coding_test/blob/main/ref/queue.md)
- [해시 체이닝 (Hash Chaining): 정수 맵핑](https://github.com/nampluskr/coding_test/blob/main/ref/hash_chaining_int.md)
- [해시 체이닝 (Hash Chaining): 문자열 맵핑](https://github.com/nampluskr/coding_test/blob/main/ref/hash_chaining_str.md)
- [우선순위 큐 (Prioirty Queue): Max. Heap](https://github.com/nampluskr/coding_test/blob/main/ref/priority_queue.md)
- [이중 우선순위 큐 (Double-ended Queue): Min. / Max. Heap](https://github.com/nampluskr/coding_test/blob/main/ref/double_ended_pq.md)
- 파티션 (Square Root Decomposition): Point Update / Range Query
- 파티션 (Square Root Decomposition): Range Update / Point Query

## 알고리즘 (함수)

- 트리 최소 공통 조상 구하기: Least Common Ancestor
- 그래프 탐색: DFS (재귀)
- 그래프 탐색: BFS (2D Grid)
- 최소 비용 경로 구하기: Dijkstra Algorithm (양의 가중치)
- 최소 비용 경로 구하기: Bellman-Ford Altorithm (음의 가중치)
- [이진 탐색: Parametric Search](https://github.com/nampluskr/coding_test/blob/main/ref/parametric_search.md)

## 수학함수

```cpp
int min(int x, int y) { return (x < y)? x: y; }
int max(int x, int y) { return (x > y)? x: y; }
```

```cpp
void swap(int& x, int& y) { int temp = x; x = y; y = temp; }
```

```cpp
int abs(int x) { return (x > 0)? x: -x; }
```

```cpp
int ceil(double x) { return -(int)(-x); }
```

```cpp
int sqrt(int n) {
    int x = n;
    int y = (x + 1) / 2;
 
    while (y < x) {
        x = y;
        y = (x + n / x) / 2;
    }
    return x;
}
```

## 문자열 함수

```cpp
int mstrlen(const char a[]) {
    int i = 0;
    while (a[i] != '\0')
        i++;
    return i;
}
```

```cpp
int mstrcmp(const char a[], const char b[]) {
    int i;
    for (i = 0; a[i] != '\0'; i++)
        if (a[i] != b[i])
            return a[i] - b[i];
    return a[i] - b[i];
}

int mstrncmp(const char a[], const char b[], int len) {
    for (int i = 0; i < len; i++)
        if (a[i] != b[i])
            return a[i] - b[i];
    return 0;
}
```

```cpp
void mstrcpy(char dest[], const char src[]) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = src[i];
}

void mstrncpy(char dest[], const char src[], int len) {
    for (int i = 0; i < len; i++)
        dest[i] = src[i];
    dest[len] = '\0';
}
```
