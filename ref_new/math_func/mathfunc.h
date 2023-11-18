#pragma once

int min(int a, int b) { return (a > b) ? b : a; }

int max(int a, int b) { return (a > b) ? a : b; }

void swap(int& a, int& b) { int temp = a; a = b; b = temp; }

int abs(int x) { return (x > 0) ? x : -x; }

int ceil(double x) { return -(int)(-x); }

// Newton's method: x[n+1] = (x[n] + x / x[n]) / 2
double sqrt(double x, double eps = 0.001) {
    double x1 = x;
    double x2 = (x1 + x / x1) / 2;
    while (x1 - x2 > eps) {
        x1 = x2;
        x2 = (x1 + x / x1) / 2;
    }
    return x2;
}