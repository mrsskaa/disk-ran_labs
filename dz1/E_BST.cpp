#include <iostream>
#include <string>
#include <algorithm>

struct Node {
    int data;
    int height;
    int size;
    Node* left;
    Node* right;
    Node* parent;
};

Node* createNode(int data) {
    Node* newNode = new Node();

    newNode->data = data;
    newNode->height = 1;
    newNode->size = 1;
    newNode->left = nullptr;
    newNode->right = nullptr;
    newNode->parent = nullptr;

    return newNode;
}

int getHeight(Node* root) {
    if (root == nullptr) {
        return 0;
    }
    return root->height;
}

int getSize(Node* root) {
    if (root == nullptr) {
        return 0;
    }
    return root->size;
}

void update(Node* root) {
    root->height = 1 + std::max(getHeight(root->left), getHeight(root->right));
    root->size = 1 + getSize(root->left) + getSize(root->right);
}

Node* rotateRight(Node* root) {
    Node* child = root->left;
    root->left = child->right;
    if (root->left != nullptr) {
        root->left->parent = root;
    }
    child->right = root;
    child->parent = root->parent;
    root->parent = child;

    update(root);
    update(child);
    return child;
}

Node* rotateLeft(Node* root) {
    Node* child = root->right;
    root->right = child->left;
    if (root->right != nullptr) {
        root->right->parent = root;
    }
    child->left = root;
    child->parent = root->parent;
    root->parent = child;

    update(root);
    update(child);
    return child;
}

Node* balance(Node* root) {
    update(root);
    int difference = getHeight(root->left) - getHeight(root->right);

    if (difference > 1) {
        if (getHeight(root->left->right) > getHeight(root->left->left)) {
            root->left = rotateLeft(root->left);
        }
        return rotateRight(root);
    }
    if (difference < -1) {
        if (getHeight(root->right->left) > getHeight(root->right->right)) {
            root->right = rotateRight(root->right);
        }
        return rotateLeft(root);
    }
    return root;
}

Node* insertNode(Node* root, int data) {
    if (root == nullptr) {
        return createNode(data);
    }

    if (data < root->data) {
        root->left = insertNode(root->left, data);
        root->left->parent = root;
    } else if (data > root->data) {
        root->right = insertNode(root->right, data);
        root->right->parent = root;
    } else {
        return root;
    }

    return balance(root);
}

Node* deleteNode(Node* root, int data) {
    if (root == nullptr) {
        return nullptr;
    }

    if (data < root->data) {
        root->left = deleteNode(root->left, data);
    } else if (data > root->data) {
        root->right = deleteNode(root->right, data);
    } else {
        if (root->left == nullptr || root->right == nullptr) {
            Node* child = root->left;
            if (child == nullptr) {
                child = root->right;
            }
            if (child != nullptr) {
                child->parent = root->parent;
            }
            delete root;
            return child;
        }

        Node* min_right = root->right;
        while (min_right->left != nullptr) {
            min_right = min_right->left;
        }
        root->data = min_right->data;
        root->right = deleteNode(root->right, min_right->data);
    }

    return balance(root);
}

Node* search_k_min(Node* root, int k) {
    while (root != nullptr) {
        int leftSize = getSize(root->left);
        if (k == leftSize + 1) {
            return root;
        }
        if (k <= leftSize) {
            root = root->left;
        } else {
            k -= leftSize + 1;
            root = root->right;
        }
    }
    return nullptr;
}

int less(Node* root, int x) {
    int count = 0;
    while (root != nullptr) {
        if (root->data < x) {
            count += getSize(root->left) + 1;
            root = root->right;
        } else {
            root = root->left;
        }
    }
    return count;
}

void deleteTree(Node* root) {
    if (root == nullptr) {
        return;
    }
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    int m;
    std::cin >> m;

    Node* root = nullptr;
    for (int i = 0; i < m; i++) {
        std::string command;
        int x;
        std::cin >> command >> x;

        if (command == "insert") {
            root = insertNode(root, x);
        } else if (command == "delete") {
            root = deleteNode(root, x);
        } else if (command == "kth") {
            std::cout << search_k_min(root, x)->data << '\n';
        } else if (command == "less") {
            std::cout << less(root, x) << '\n';
        }
    }

    deleteTree(root);
    return 0;
}
