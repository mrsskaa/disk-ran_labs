#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

void update(std::vector<long long>& bit, int i) {
    int n = bit.size();

    while (i < n) {
        bit[i]++;
        i += i & (-i);
    }
}

long long sum(const std::vector<long long>& bit, int i) {
    long long result = 0;

    while (i > 0) {
        result += bit[i];
        i -= i & (-i);
    }

    return result;
}

long long count(const std::vector<long long>& bit, int l, int r) {
    if (l > r) {
        return 0;
    }

    return sum(bit, r) - sum(bit, l - 1);
}

int main() {
    int q;
    std::cin >> q;

    std::vector<std::string> commands(q);
    std::vector<long long> t(q), T(q);
    std::vector<long long> times;

    for (int i = 0; i < q; i++) {
        std::cin >> commands[i];

        if (commands[i] == "event") {
            std::cin >> t[i];
            times.push_back(t[i]);
        }
        else if (commands[i] == "count") {
            std::cin >> t[i] >> T[i];
        }
    }

    std::sort(times.begin(), times.end());
    times.erase(std::unique(times.begin(), times.end()),times.end());

    std::vector<long long> bit(times.size() + 1, 0);

    for (int i = 0; i < q; i++) {
        if (commands[i] == "event") {
            int d = std::lower_bound(times.begin(), times.end(), t[i]) - times.begin() + 1;

            update(bit, d);
        }
        else if (commands[i] == "count") {
            long long start = t[i] - T[i] + 1;

            int l = std::lower_bound(times.begin(), times.end(), start) - times.begin() + 1;

            int r = std::upper_bound(times.begin(), times.end(), t[i]) - times.begin();

            std::cout << count(bit, l, r) << '\n';
        }
    }

    return 0;
}