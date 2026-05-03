#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// ================================================================
//  Node
// ================================================================

struct Node {
    int   key;
    int   height;
    int   size;        // subtree size - used by kthSmallest
    Node* left;
    Node* right;

    Node(int k)
        : key(k), height(1), size(1), left(nullptr), right(nullptr) {}
};

// ================================================================
//  Basic helpers
// ================================================================

int getHeight(Node* n) {
    if (!n) return 0;
    return 1 + max(getHeight(n->left), getHeight(n->right)); 
}

int getSize(Node* n) {
    return n ? n->size : 0;
}

void updateNode(Node* n) {
    if (n) {
        n->height = 1 + max(getHeight(n->left), getHeight(n->right));
        n->size   = 1 + getSize(n->left) + getSize(n->right);
    }
}

int getBalance(Node* n) {
    return n ? getHeight(n->left) - getHeight(n->right) : 0;
}

// ================================================================
//  Rotations
// ================================================================

Node* rotateRight(Node* y) {
    Node* x  = y->left;
    Node* T2 = x->right;

    x->right = y;
    x->left  = y->left;    

    updateNode(y);
    updateNode(x);
    return x;
}

Node* rotateLeft(Node* x) {
    Node* y  = x->right;
    Node* T2 = y->left;

    y->left  = x;
    y->right = x->right;   

    updateNode(x);
    updateNode(y);
    return y;
}

// ================================================================
//  Rebalance
// ================================================================

Node* balance(Node* n) {
    updateNode(n);
    int bf = getBalance(n);

    // Left-heavy
    if (bf > 1) {
        if (getBalance(n->left) > 0)        
            n->left = rotateLeft(n->left);
        return rotateRight(n);
    }

    // Right-heavy
    if (bf < -1) {
        if (getBalance(n->right) < 0)       
            n->right = rotateRight(n->right);
        return rotateLeft(n);
    }

    return n;
}

// ================================================================
//  Insert
// ================================================================

Node* insert(Node* n, int key) {
    if (!n) return new Node(key);

    if (key <= n->key)                      
        n->left  = insert(n->left,  key);
    else
        n->right = insert(n->right, key);

    return balance(n);
}

// ================================================================
//  Successor helper  +  Delete
// ================================================================

Node* getMinNode(Node* n) {
    while (n->right) n = n->right;        
    return n;
}

Node* deleteNode(Node* n, int key) {
    if (!n) return n;

    if      (key < n->key) n->left  = deleteNode(n->left,  key);
    else if (key > n->key) n->right = deleteNode(n->right, key);
    else {
        if (!n->left || !n->right) {
            Node* child = n->left ? n->left : n->right;
            if (!child) { delete n; return nullptr; }
            *n = *child;
            delete child;
        } else {
            Node* succ = getMinNode(n->right);   
            n->key     = succ->key;
            n->left    = deleteNode(n->left, succ->key);   
        }
    }
    return balance(n);
}

// ================================================================
//  Search
// ================================================================

bool search(Node* n, int key) {
    if (!n)            return false;
    if (key == n->key) return true;
    if (key <  n->key) return search(n->left,  key);
                       return search(n->right, key);
}

// ================================================================
//  Inorder
// ================================================================

static vector<int> _inBuf;

void inorder(Node* n) {
    if (!n) return;
    inorder(n->left);
    _inBuf.push_back(n->key);
    inorder(n->right);
}

// ================================================================
//  Kth-smallest
// ================================================================

int kthSmallest(Node* n, int k) {
    if (!n) return -1;
    int leftSize = getSize(n->left);
    if      (k <= leftSize)       return kthSmallest(n->left,  k);
    else if (k == leftSize + 1)   return n->key;
    else                          return kthSmallest(n->right, k - leftSize);   // BUG #4
}

// ================================================================
//  Public height
// ================================================================

int treeHeight(Node* n) {
    if (!n) return 0;
    return getHeight(n) - 1;       
}

// ================================================================
//  Main
// ================================================================

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Node* root = nullptr;
    int Q;  cin >> Q;

    while (Q--) {
        string op;  cin >> op;

        if (op == "INSERT") {
            int x;  cin >> x;
            root = insert(root, x);

        } else if (op == "DELETE") {
            int x;  cin >> x;
            root = deleteNode(root, x);

        } else if (op == "SEARCH") {
            int x;  cin >> x;
            cout << (search(root, x) ? "FOUND" : "NOT FOUND") << "\n";

        } else if (op == "INORDER") {
            inorder(root);
            for (int i = 0; i < (int)_inBuf.size(); i++) {
                if (i) cout << " ";
                cout << _inBuf[i];
            }
            cout << "\n";

        } else if (op == "HEIGHT") {
            cout << treeHeight(root) << "\n";

        } else if (op == "KTHSMALLEST") {
            int k;  cin >> k;
            cout << kthSmallest(root, k) << "\n";
        }
    }

    return 0;
}
