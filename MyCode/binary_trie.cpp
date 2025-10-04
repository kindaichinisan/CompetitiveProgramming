#include<bits/stdc++.h>
using namespace std;

class binary_trie{

public:
    struct node {
        node *nxt[2];
        bool is_end;
        int level;
        
        node(int _level) {
            for (int i = 0; i < 2; i++) nxt[i] = NULL;
            is_end = false;
            level=_level;
        }
    };

    node *root;
    
    binary_trie(){
        root=new node(0);
    }

    void insert(int num) {
        node *cur = root;

        for (int i = 31; i >= 0; i--) {
            int bit = (num >> i) & 1;
            if (cur->nxt[bit] == NULL){
                cur->nxt[bit] = new node(cur->level+1);
            }
            cur = cur->nxt[bit];
        }
        // cur -> last node
        cur->is_end = true;
    }

    //to use with xor question when opposite bit is preferred.
    int query(int x) {
        node *cur = root;
        if (!cur->nxt[0] && !cur->nxt[1]) return -1; // empty trie
        int res = 0;
        for (int i = 31; i >= 0; i--) {
            int bit = (x >> i) & 1;
            int prefer = 1 - bit; // opposite bit preferred
            if (cur->nxt[prefer]) {
                res |= (1 << i);
                cur = cur->nxt[prefer];
            } else {
                cur = cur->nxt[bit];
            }
        }
        return res;
    }
};