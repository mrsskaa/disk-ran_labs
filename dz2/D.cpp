#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <string>

struct Node {
    int l, r;
    long long value;
    Node* left;
    Node* right;
};

Node* createNode(int l, int r, const std::vector<long long>& t) {
    Node* temp = new Node();
    temp->l = l;
    temp->r = r;
    temp->left = nullptr;
    temp->right = nullptr;

    if (l == r) {
        temp->value = t[l-1];
        return temp;
    }

    temp->left = createNode(l, (r+l)/2, t);
    temp->right = createNode((r+l)/2+1, r, t);
    temp->value = std::min(temp->left->value, temp->right->value);

    return temp;
}

long long find_min(Node* root, long long l, long long r) {
    if (root == nullptr) {
        return LLONG_MAX;
    }

    if (root->r <= r && root->l >= l) {
        return root->value;
    }

    else if (root->r < l || root->l > r) {
        return LLONG_MAX;
    }

    long long leftMin = find_min(root->left, l, r);
    long long rightMin = find_min(root->right, l, r);

    return std::min(leftMin, rightMin);
}

void set(Node* root, long long d, long long v) {
    if (root == nullptr) {
        return;
    }
    if (root->r == root->l) {
        root->value = v;
        return;
    }

    if (root->left->r >= d) {
        set(root->left, d, v);
    }
    else {
        set(root->right, d, v);
    }

    root->value = std::min(root->left->value, root->right->value);
}


int main() {
    long long n, q, l, r, d, v;
    std::string command;

    std::cin >> n >> q;

    std::vector<long long> t(n);

    for (long long i = 0; i < n; i++) {
        std::cin >> t[i];
    }

    Node* root = createNode(1, n, t);

    for (long long i = 0; i < q; ++i) {
        std::cin >> command;

        if (command == "min") {
            std::cin >> l >> r;
            std::cout << find_min(root, l, r) << std::endl;
        }
        else if (command == "set") {
            std::cin >> d >> v;
            set(root, d, v);
        }
        else {
            break;
        }
    }


    return 0;

}