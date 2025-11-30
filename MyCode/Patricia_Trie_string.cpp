#include <bits/stdc++.h>
using namespace std;

// chatgpt not verified yet.
class Patricia_Trie_string {
public:
    struct Node {
        bool is_end;
        string edge;  // compressed edge label from parent
        unordered_map<char, Node*> nxt;

        Node(string e = "") : is_end(false), edge(e) {}
    };

    Node* root;

    Patricia_Trie_string() {
        root = new Node("");
    }

    // longest common prefix length between a and b
    int lcp(const string &a, const string &b) {
        int L = min(a.size(), b.size());
        for (int i = 0; i < L; i++)
            if (a[i] != b[i]) return i;
        return L;
    }

    void insert(const string &s) {
        insert_rec(root, s);
    }

    void insert_rec(Node* cur, const string &s) {
        if (s.empty()) {
            cur->is_end = true;
            return;
        }

        char c = s[0];

        // Case 1: no child with matching first letter → new leaf
        if (!cur->nxt.count(c)) {
            Node* leaf = new Node(s);
            leaf->is_end = true;
            cur->nxt[c] = leaf;
            return;
        }

        Node* child = cur->nxt[c];
        string &edge = child->edge;

        int k = lcp(edge, s);

        // Case 2: edge fully matches → go deeper with remainder
        if (k == edge.size()) {
            insert_rec(child, s.substr(k));
            return;
        }

        // Case 3: partial match → split edge
        // Split existing child into two:

        // 1) New parent node replacing old edge prefix
        Node* newParent = new Node(edge.substr(0, k));

        // 2) Old child becomes a child of new parent with remaining edge
        child->edge = edge.substr(k);
        newParent->nxt[ child->edge[0] ] = child;

        // 3) New leaf for inserted string remainder
        string rest_new = s.substr(k);
        Node* newLeaf = new Node(rest_new);
        newLeaf->is_end = true;
        newParent->nxt[ rest_new[0] ] = newLeaf;

        // Place newParent under current node
        cur->nxt[c] = newParent;
    }

    bool search(const string &s) {
        return search_rec(root, s);
    }

    bool search_rec(Node* cur, const string &s) {
        if (s.empty()) return cur->is_end;

        char c = s[0];
        if (!cur->nxt.count(c)) return false;

        Node* child = cur->nxt[c];
        string &edge = child->edge;

        // Edge must be full prefix of s
        if (s.size() < edge.size() || s.compare(0, edge.size(), edge) != 0)
            return false;

        // Continue with remainder
        return search_rec(child, s.substr(edge.size()));
    }
};