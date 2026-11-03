#include <iostream>
#include <vector>
#include <algorithm>
#include <string>


struct Node {
    int l, r;
    long long sum, pref, suff, best;
    Node* left;
    Node* right;
};

Node* createNode(int l, int r, const std::vector<long long>& a) {
    Node* temp = new Node();
    temp->l = l;
    temp->r = r;
    temp->left = nullptr;
    temp->right = nullptr;

    if (l == r) {
        temp->sum = a[l-1];
        temp->pref = a[l-1];
        temp->suff = a[l-1];
        temp->best = a[l-1];
        return temp;
    }

    temp->left = createNode(l, (r+l)/2, a);
    temp->right = createNode((r+l)/2+1, r, a);

    temp->sum = temp->left->sum + temp->right->sum;
    temp->pref = std::max(temp->left->pref, temp->left->sum + temp->right->pref);
    temp->suff = std::max(temp->right->suff, temp->right->sum + temp->left->suff);
    temp->best = std::max({temp->left->suff + temp->right->pref, temp->left->best, temp->right->best});

    return temp;
}

Node best(Node* root, long long l, long long r) {
    if (root == nullptr) {
        return Node{1, 0};
    }

    if (root->r <= r && root->l >= l) {
        return *root;
    }

    if (root->r < l || root->l > r) {
        return Node{1, 0};
    }

    Node leftBest = best(root->left, l, r);
    Node rightBest = best(root->right, l, r);

    if (leftBest.l > leftBest.r) {
        return rightBest;
    }
    if (rightBest.l > rightBest.r) {
        return leftBest;
    }

    Node temp;
    temp.l = leftBest.l;
    temp.r = rightBest.r;
    temp.sum = leftBest.sum + rightBest.sum;
    temp.pref = std::max(leftBest.pref, leftBest.sum + rightBest.pref);
    temp.suff = std::max(rightBest.suff, rightBest.sum + leftBest.suff);
    temp.best = std::max({leftBest.suff + rightBest.pref, leftBest.best, rightBest.best});

    return temp;
}

void update(Node* root, long long d, long long v) {
    if (root == nullptr) {
        return;
    }
    if (root->r == root->l) {
        root->sum = v;
        root->pref = v;
        root->suff = v;
        root->best = v;
        return;
    }

    if (root->left->r >= d) {
        update(root->left, d, v);
    }
    else {
        update(root->right, d, v);
    }

    root->sum = root->left->sum + root->right->sum;
    root->pref = std::max(root->left->pref, root->left->sum + root->right->pref);
    root->suff = std::max(root->right->suff, root->right->sum + root->left->suff);
    root->best = std::max({root->left->suff + root->right->pref, root->left->best, root->right->best});
}


int main() {
    long long n, q, l, r, d, v;
    std::string command;

    std::cin >> n >> q;

    std::vector<long long> a(n);

    for (long long i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    Node* root = createNode(1, n, a);

    for (long long i = 0; i < q; ++i) {
        std::cin >> command;

        if (command == "best") {
            std::cin >> l >> r;
            std::cout << best(root, l, r).best << std::endl;
        }
        else if (command == "update") {
            std::cin >> d >> v;
            update(root, d, v);
        }
        else {
            break;
        }
    }

    return 0;
}