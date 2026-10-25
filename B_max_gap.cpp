#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

struct Bucket {
    long double min = 0;
    long double max = 0;
    bool used = false;
};

long double maxGap(std::vector<long double> a) {
    int n = a.size();


    if (n < 2) {
        return 0;
    }

    long double minimum = a[0];
    long double maximum = a[0];
    for (int i = 1; i < n; i++) {
        minimum = std::min(minimum, a[i]);
        maximum = std::max(maximum, a[i]);
    }

    if (minimum == maximum) {
        return 0;
    }

    long double range = maximum - minimum;
    std::vector<Bucket> buckets(n);

    for (long double x : a) {
        int index = ((x - minimum) / range) * (n - 1);
        if (index >= n) {
            index = n - 1;
        }

        Bucket& bucket = buckets[index];
        if (!bucket.used) {
            bucket.min = x;
            bucket.max = x;
            bucket.used = true;
        } else {
            bucket.min = std::min(bucket.min, x);
            bucket.max = std::max(bucket.max, x);
        }
    }

    long double answer = 0;
    long double previous = minimum;
    for (const Bucket& bucket : buckets) {
        if (bucket.used) {
            answer = std::max(answer, bucket.min - previous);
            previous = bucket.max;
        }
    }

    return answer;
}

int main() {
    int n;
    std::cin >> n;

    std::vector<long double> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    std::cout << std::setprecision(15) << maxGap(a) << '\n';
}
