#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

int query(vector<int>& arr, int start, int left) {
    auto argmin = min_element(next(arr.begin(), start), next(arr.begin(), start + left));
    return argmin;
}


long long solve(vector<int>& arr, int start, int end) {
    int n = arr.size();
    int idx = query(arr, start, end);
    long long area = (long long)(end - start + 1) * (long long)arr[idx];

    if (start < idx)
        area = max(area, solve(arr, start, idx - 1));
    if (idx < end)
        area = max(area, solve(arr, idx + 1, end));
    return area;
}

int main()
{
    setbuf(stdout, NULL);
    freopen("sample_input.txt", "r", stdin);

    int n, x;
    while (true) {
        scanf("%d", &n);
        if (n == 0) break;

        vector<int> arr(n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
        }

        int ret = solve(arr, 0, n - 1);
        printf("%d\n", ret);
    }

    return 0;
}