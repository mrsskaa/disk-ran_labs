#include <iostream>
#include <vector>

int lowerBound(const std::vector<long long>& a, long long x) {
    int left = 0;
    int right = a.size();

    while (left < right) {
        int mid = left + (right - left) / 2;
        if (a[mid] < x) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    return left;
}

int upperBound(const std::vector<long long>& a, long long x) {
    int left = 0;
    int right = a.size();

    while (left < right) {
        int mid = left + (right - left) / 2;
        if (a[mid] <= x) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    return left;
}

int main() {
    int n, q;
    std::cin >> n >> q;

    std::vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    for (int i = 0; i < q; i++) {
        long long x;
        std::cin >> x;

        int lower = lowerBound(a, x);
        int upper = upperBound(a, x);
        int count = upper - lower;

        if (lower == n) {
            lower = -1;
        }
        if (upper == n) {
            upper = -1;
        }

        std::cout << lower << ' ' << upper << ' ' << count << '\n';
    }
}
