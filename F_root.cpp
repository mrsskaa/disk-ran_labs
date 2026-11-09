#include <iostream>

bool powerFits(unsigned long long x, int k, unsigned long long a) {
    if (x == 0) {
        return true;
    }

    unsigned long long product = 1;
    for (int i = 0; i < k; i++) {
        if (product > a / x) {
            return false;
        }
        product *= x;
    }
    return true;
}

unsigned long long findRoot(unsigned long long a, int k) {
    unsigned long long left = 0;
    unsigned long long right = a;

    while (left < right) {
        unsigned long long mid = right - (right - left) / 2;
        if (powerFits(mid, k, a)) {
            left = mid;
        } else {
            right = mid - 1;
        }
    }

    return left;
}

int main() {
    unsigned long long a;
    int k;
    std::cin >> a >> k;

    std::cout << findRoot(a, k) << '\n';
}
