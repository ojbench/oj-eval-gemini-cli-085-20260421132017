#include <iostream>

struct Node {
    int val;
    Node *left, *right;
    Node(int v) : val(v), left(nullptr), right(nullptr) {}
};

bool end_of_input = false;

Node* build() {
    if (end_of_input) return nullptr;
    int val;
    if (!(std::cin >> val)) {
        end_of_input = true;
        return nullptr;
    }
    if (val == -2) {
        end_of_input = true;
        return nullptr;
    }
    if (val == -1) return nullptr;
    Node* node = new Node(val);
    node->left = build();
    node->right = build();
    return node;
}

Node* prune(Node* root) {
    if (!root) return nullptr;
    root->left = prune(root->left);
    root->right = prune(root->right);
    if (root->val == 0 && !root->left && !root->right) {
        delete root;
        return nullptr;
    }
    return root;
}

void print(Node* root, bool& first) {
    if (!first) std::cout << " ";
    first = false;
    if (!root) {
        std::cout << -1;
        return;
    }
    std::cout << root->val;
    print(root->left, first);
    print(root->right, first);
}

void deleteTree(Node* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    Node* root = build();
    root = prune(root);
    bool first = true;
    print(root, first);
    std::cout << std::endl;
    deleteTree(root);
    return 0;
}
