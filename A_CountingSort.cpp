#include <iostream>
#include <string>
#include <vector>

struct Actor {
    std::string name;
    int age;
};

void countingSort(std::vector<Actor>& a) {
    int n = a.size();
    std::vector<Actor> b(n);
    std::vector<int> c(121, 0);

    for (int i = 0; i < n; i++) {
        c[a[i].age]++;
    }

    for (int i = 1; i < 121; i++) {
        c[i] += c[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {
        int age = a[i].age;
        b[c[age] - 1] = a[i];
        c[age]--;
    }

    a.swap(b);
}

int main() {
    int n;
    std::cin >> n;

    std::vector<Actor> actors(n);
    for (Actor& actor : actors) {
        std::cin >> actor.name >> actor.age;
    }

    countingSort(actors);

    for (const Actor& actor : actors) {
        std::cout << actor.name << ' ' << actor.age << '\n';
    }
}
