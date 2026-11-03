#include <iostream>
#include <vector>

struct Node {
    int l, r;
    int cnt;
    Node* left;
    Node* right;
};

Node* createNode(int l, int r) {
    Node* temp = new Node();
    temp->l = l;
    temp->r = r;
    temp->cnt = r-l+1;
    temp->left = nullptr;
    temp->right = nullptr;

    if (l == r) {
        return temp;
    }

    temp->left = createNode(l, (r+l)/2);
    temp->right = createNode((r+l)/2+1, r);

    return temp;
}

long long sell(Node* root, long long k) {
    long long place;

    if (root == nullptr) {
        return -1;
    }

    if (root -> l == root -> r) {
        root -> cnt = 0;
        return root->l;
    }

    if (k <= root->left->cnt) {
        place = sell(root->left, k);
    }
    else {
        k -= root->left->cnt;
        place = sell(root->right, k);
    }

    root->cnt = root->left->cnt + root->right->cnt;

    return place;
}

void returnSeat(Node* root, long long k) {
    if (root->l == root->r) {
        root->cnt = 1;
        return;
    }

    if (k <= root->left->r) {
        returnSeat(root->left, k);
    }
    else {
        returnSeat(root->right, k);
    }

    root->cnt = root->left->cnt + root->right->cnt;
}


int main() {
    long long n, q, k;
    std::string command;

    std::cin >> n >> q;

    Node* root = createNode(1, n);

    for (long long i = 0; i < q; ++i) {
        std::cin >> command;
        std::cin >> k;

        if (command == "sell") {
            std::cout << sell(root, k) << std::endl;
        }
        else if (command == "return") {
            returnSeat(root, k);
        }
        else {
            break;
        }
    }


    return 0;

}