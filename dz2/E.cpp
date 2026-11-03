#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

struct Node {
    int l, r, lazy;
    long long pref, suff, best;
    Node* left;
    Node* right;
};

Node* createNode(int l, int r) {
    Node* temp = new Node();
    temp->l = l;
    temp->r = r;
    temp->left = nullptr;
    temp->right = nullptr;
    temp->pref = 0;
    temp->suff = 0;
    temp->best = 0;
    temp->lazy = -1;

    if (l == r) {
        return temp;
    }

    temp->left = createNode(l, (r+l)/2);
    temp->right = createNode((r+l)/2+1, r);

    return temp;
}

void push(Node* root) {
    if (root == nullptr || root->lazy == -1) {
        return;
    }

    if (root->left != nullptr) {
        root->left->lazy = root->lazy;

        long long len = root->left->r - root->left->l + 1;

        if (root->lazy == 1) {
            root->left->pref = len;
            root->left->suff = len;
            root->left->best = len;
        }
        else {
            root->left->pref = 0;
            root->left->suff = 0;
            root->left->best = 0;
        }
    }

    if (root->right != nullptr) {
        root->right->lazy = root->lazy;

        long long len = root->right->r - root->right->l + 1;

        if (root->lazy == 1) {
            root->right->pref = len;
            root->right->suff = len;
            root->right->best = len;
        }
        else {
            root->right->pref = 0;
            root->right->suff = 0;
            root->right->best = 0;
        }
    }

    root->lazy = -1;
}

void on(Node* root, long long l, long long r) {
    if (root == nullptr || root->r < l || root->l > r) {
        return;
    }

    if (root->l >= l && root->r <= r) {
        long long len = root->r - root->l + 1;

        root->pref = len;
        root->suff = len;
        root->best = len;
        root->lazy = 1;
        return;
    }

    push(root);

    on(root->left, l, r);
    on(root->right, l, r);

    long long leftLen = root->left->r - root->left->l + 1;
    long long rightLen = root->right->r - root->right->l + 1;

    root->pref = root->left->pref;

    if (root->left->pref == leftLen) {
        root->pref += root->right->pref;
    }

    root->suff = root->right->suff;

    if (root->right->suff == rightLen) {
        root->suff += root->left->suff;
    }

    root->best = std::max({root->left->best, root->right->best, root->left->suff + root->right->pref});
}

void off(Node* root, long long l, long long r) {
    if (root == nullptr || root->r < l || root->l > r) {
        return;
    }

    if (root->l >= l && root->r <= r) {
        root->pref = 0;
        root->suff = 0;
        root->best = 0;
        root->lazy = 0;
        return;
    }

    push(root);

    off(root->left, l, r);
    off(root->right, l, r);

    long long leftLen = root->left->r - root->left->l + 1;
    long long rightLen = root->right->r - root->right->l + 1;

    root->pref = root->left->pref;

    if (root->left->pref == leftLen) {
        root->pref += root->right->pref;
    }

    root->suff = root->right->suff;

    if (root->right->suff == rightLen) {
        root->suff += root->left->suff;
    }

    root->best = std::max({
        root->left->best,
        root->right->best,
        root->left->suff + root->right->pref
    });
}

Node max(Node* root, long long l, long long r) {
    if (root == nullptr || root->r < l || root->l > r) {
        return Node{1, 0};
    }

    if (root->l >= l && root->r <= r) {
        return *root;
    }

    push(root);

    Node leftBest = max(root->left, l, r);
    Node rightBest = max(root->right, l, r);

    if (leftBest.l > leftBest.r) {
        return rightBest;
    }

    if (rightBest.l > rightBest.r) {
        return leftBest;
    }

    Node temp{};
    temp.l = leftBest.l;
    temp.r = rightBest.r;

    long long leftLen = leftBest.r - leftBest.l + 1;
    long long rightLen = rightBest.r - rightBest.l + 1;

    temp.pref = leftBest.pref;

    if (leftBest.pref == leftLen) {
        temp.pref += rightBest.pref;
    }

    temp.suff = rightBest.suff;

    if (rightBest.suff == rightLen) {
        temp.suff += leftBest.suff;
    }

    temp.best = std::max({
        leftBest.best,
        rightBest.best,
        leftBest.suff + rightBest.pref
    });

    return temp;
}

int main() {
    long long n, q, l, r;
    std::string command;

    std::cin >> n >> q;

    Node* root = createNode(1, n);

    for (long long i = 0; i < q; ++i) {
        std::cin >> command;
        std::cin >> l >> r;

        if (command == "max") {
            std::cout << max(root, l, r).best << std::endl;
        }
        else if (command == "on") {
            on(root, l, r);
        }
        else if (command == "off") {
            off(root, l, r);
        }
        else {
            break;
        }
    }

    return 0;
}