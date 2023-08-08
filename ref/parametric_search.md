### [Parametric Search]

```cpp
bool is_possible(int mid, int target) {
    int temp;
    for (int i = 0; i < NUM_DATA; i++>) { temp += data[i];}
    return temp >= target;
}

while () {
    int mid = (start + end) / 2;
    if (is_possible(mid)) { start = mid -1; }
    else { end = mid - 1;}
}
```

### [BOJ_2512_예산]

```cpp
// BOJ 2512 예산
#include <stdio.h>

#define NUM_DATA    4

inline int min(int a, int b) { return (a < b) ? a : b; }
inline int max(int a, int b) { return (a > b) ? a : b; }

int search(int data[], int start, int end, int target) {
    int sol = -1;

    while (start <= end) {
        int mid = (start + end) / 2;
        int sum = 0;

        for (int i = 0; i < NUM_DATA; i++) { sum += min(data[i], mid); }

        if (sum <= target) {
            sol = mid;
            start = mid + 1;
        }
        else { end = mid - 1; }
    }
    return sol;
}

int main()
{
    int data[NUM_DATA] = { 120, 110, 140, 150 };
    int target = 485;
    int ret;    // ans = 127

    int start = 0;
    int end = 0;
    for (int i = 0; i < NUM_DATA; i++) {
        end = max(end, data[i]);
    }

    ret = search(data, start, end, target);
    printf(">> Result: %d\n", ret);

    return 0;    // return end;
}
```

### [BOJ_1654_랜선자르기]

```cpp
// BOJ 1654 랜선자르기
#include <stdio.h>

#define NUM_DATA 4

inline int min(int a, int b) { return (a < b) ? a : b; }
inline int max(int a, int b) { return (a > b) ? a : b; }

int search(int data[], int start, int end, int target) {
    int sol = -1;

    while (start <= end) {
        int mid = (start + end) / 2;
        int sum = 0;

        for (int i = 0; i < NUM_DATA; i++) { sum += data[i] / mid; }

        if (sum >= target) {
            start = mid + 1;
            if (sol < mid) { sol = mid; }
        }
        else { end = mid - 1; }
    }
    return sol;
}

int main()
{
    int data[NUM_DATA] = { 802, 743, 457, 539 };
    int target = 11;
    int ret;    // ans = 200

    int start = 1;
    int end = 0;
    for (int i = 0; i < NUM_DATA; i++) {
        end = max(end, data[i]);
    }

    ret = search(data, start, end, target);
    printf(">> Result: %d\n", ret);

    return 0;
}
```

### [BOJ_2805_나무자르기]

```cpp
// BOJ 2805 나무자르기
#include <stdio.h>

#define NUM_DATA    5

inline int min(int a, int b) { return (a < b) ? a : b; }
inline int max(int a, int b) { return (a > b) ? a : b; }

int search(int data[], int start, int end, int target) {
    int sol = -1;

    while (start <= end) {
        int mid = (start + end) / 2;
        int sum = 0;
        for (int i = 0; i < NUM_DATA; i++) {
            if (mid <= data[i]) { sum += data[i] - mid; }
        }
        if (sum >= target) {
            sol = mid;
            start = mid + 1;
        }
        else { end = mid - 1; }
    }
    return sol; // return end;
}

int main()
{
    int data[NUM_DATA] = {4, 42, 40, 26, 46};
    int target = 20;    
    int ret;    // and = 36

    int start = 0;
    int end = 0;
    for (int i = 0; i < NUM_DATA; i++) { end = max(end, data[i]); }

    ret = search(data, start, end, target);
    printf(">> Result: %d\n", ret);
    return 0;
}
```