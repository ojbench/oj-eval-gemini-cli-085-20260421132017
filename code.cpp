#include <iostream>

// Node structure for the binary tree
struct Node {
    int val;
    Node *left, *right;
    Node(int v) : val(v), left(nullptr), right(nullptr) {}
};

bool end_of_input = false;

// Build the tree from extended preorder traversal
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

// Prune subtrees that contain only 0s
Node* prune(Node* root) {
    if (!root) return nullptr;
    root->left = prune(root->left);
    root->right = prune(root->right);
    // If current node is 0 and both children are null (either originally or after pruning), prune it
    if (root->val == 0 && !root->left && !root->right) {
        delete root;
        return nullptr;
    }
    return root;
}

// Print the tree in extended preorder traversal
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

// Clean up memory
void deleteTree(Node* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    // Speed up I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    Node* root = build();
    root = prune(root);

    bool first = true;
    print(root, first);
    std::cout << "\n";

    deleteTree(root);
    return 0;
}
