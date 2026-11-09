#include <cstdio>
#include <vector>
#include <utility>

class Heap {
    std::vector<int> a;
    bool isMin;

    bool higher(int x, int y) const {
        if (isMin) {
            return x < y;
        }
        return x > y;
    }

    void siftUp(int i) {
        while (i > 0) {
            int parent = (i - 1) / 2;
            if (!higher(a[i], a[parent])) {
                break;
            }
            std::swap(a[i], a[parent]);
            i = parent;
        }
    }

    void siftDown(int i) {
        int n = a.size();
        while (2 * i + 1 < n) {
            int child = 2 * i + 1;
            if (child + 1 < n && higher(a[child + 1], a[child])) {
                child++;
            }
            if (!higher(a[child], a[i])) {
                break;
            }
            std::swap(a[i], a[child]);
            i = child;
        }
    }

public:
    Heap(bool isMin) : isMin(isMin) {}

    int size() const {
        return a.size();
    }

    int top() const {
        return a[0];
    }

    void push(int x) {
        a.push_back(x);
        siftUp(a.size() - 1);
    }

    void pop() {
        a[0] = a.back();
        a.pop_back();
        if (!a.empty()) {
            siftDown(0);
        }
    }
};

int main() {
    int n;
    std::scanf("%d", &n);

    Heap left(false);
    Heap right(true);

    for (int i = 0; i < n; i++) {
        int x;
        std::scanf("%d", &x);

        if (left.size() == 0 || x <= left.top()) {
            left.push(x);
        } else {
            right.push(x);
        }

        if (left.size() > right.size() + 1) {
            right.push(left.top());
            left.pop();
        } else if (right.size() > left.size()) {
            left.push(right.top());
            right.pop();
        }

        if (i > 0) {
            std::printf(" ");
        }
        std::printf("%d", left.top());
    }
    std::printf("\n");
}
