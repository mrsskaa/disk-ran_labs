#include <iostream>
#include <vector>
#include <string>

struct Node {
    int children[26]{};
    std::vector<int> top;
};

std::vector<Node> nodes;

int createNode() {
    nodes.emplace_back();
    return static_cast<int>(nodes.size()) - 1;
}

bool cmp(int a, int b, const std::vector<std::string>& words,
         const std::vector<long long>& freq) {
    if (freq[a] != freq[b]) {
        return freq[a] > freq[b];
    }

    return words[a] < words[b];
}

void add(int root, const std::string& w, long long f,
         std::vector<std::string>& words,
         std::vector<long long>& freq) {
    int id = words.size();

    words.push_back(w);
    freq.push_back(f);

    int temp = root;

    for (int i = 0; i < w.size(); i++) {
        int d = w[i] - 'a';

        if (nodes[temp].children[d] == 0) {
            int child = createNode();
            nodes[temp].children[d] = child;
        }

        temp = nodes[temp].children[d];

        int pos = 0;

        while (pos < nodes[temp].top.size() &&
               !cmp(id, nodes[temp].top[pos], words, freq)) {
            pos++;
        }

        if (pos < 3) {
            nodes[temp].top.insert(nodes[temp].top.begin() + pos, id);

            if (nodes[temp].top.size() > 3) {
                nodes[temp].top.pop_back();
            }
        }
    }
}

void suggest(int root, const std::string& p,
             const std::vector<std::string>& words) {
    int temp = root;

    for (int i = 0; i < p.size(); i++) {
        int d = p[i] - 'a';

        if (nodes[temp].children[d] == 0) {
            std::cout << "-\n";
            return;
        }

        temp = nodes[temp].children[d];
    }

    if (nodes[temp].top.empty()) {
        std::cout << "-\n";
        return;
    }

    for (int i = 0; i < nodes[temp].top.size(); i++) {
        if (i > 0) {
            std::cout << " ";
        }

        std::cout << words[nodes[temp].top[i]];
    }

    std::cout << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int q;
    std::string command, p;
    std::vector<std::string> words;
    std::vector<long long> freq;

    std::cin >> q;

    nodes.reserve(1000001);
    int root = createNode();

    for (int i = 0; i < q; i++) {
        std::cin >> command;

        if (command == "add") {
            std::string w;
            long long f;

            std::cin >> w >> f;

            add(root, w, f, words, freq);
        }
        else if (command == "suggest") {
            std::cin >> p;

            suggest(root, p, words);
        }
    }

    return 0;
}