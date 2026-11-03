#include <algorithm>
#include <iostream>
#include <vector>

std::vector<int> merge(int l, int r, const std:: vector<int>& a, long long& cnt) {
    int mid = (r+l)/2, i = 0, j = 0;
    std::vector <int> m;

    if (r-l <= 1) {
        if (r == l) {
            return {};
        }
        return {a[l]};
    }

    std::vector<int> x = merge(l, mid, a, cnt);
    std::vector<int> y = merge(mid, r, a, cnt);

    while (i < x.size() && j < y.size()) {
        if (x[i] > y[j]) {
            m.push_back(y[j]);
            j++;
            cnt += x.size()-i;
        }
        else {
            m.push_back(x[i]);
            i++;
        }
    }

    while (i < x.size()) {
        m.push_back(x[i]);
        i++;
    }

    while (j < y.size()) {
        m.push_back(y[j]);
        j++;
    }

    return m;


}

int main() {
    long long n, cnt = 0, first = 0, second = 1;

    std::cin >> n;

    std::vector <int> a(n);

    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    merge(0,n, a,cnt);

    std::cout << cnt;


    return 0;

}