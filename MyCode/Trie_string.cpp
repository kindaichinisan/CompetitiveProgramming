#include<bits/stdc++.h>
using namespace std;

class Trie_string{

public:
    struct node {
        node *nxt[26];
        bool is_end;
        int level;
        
        node(int _level) {
            for (int i = 0; i < 26; i++) nxt[i] = NULL;
            is_end = false;
            level=_level;
        }
    };

    node *root;
    
    Trie_string(){
        root=new node(0);
    }

    //first letter will be at level1.
    void insert(string s) {
        //printf("%s\n", s.c_str());
        node *cur = root;
        for (int i = 0; i < s.size(); i++) {
            int imap = s[i] - 'a';
            // new node
            if (cur->nxt[imap] == NULL) {
                cur->nxt[imap] = new node(cur->level+1);
                
            }
            // goto that node
            cur = cur->nxt[imap];
        }
        // cur -> last node
        cur->is_end = true;
    }

    //O(|s|)
    bool search(string s) {
        node *cur = root;
        for (int i = 0; i < s.size(); i++) {
            int imap = s[i] - 'a';
            if (cur->nxt[imap] == NULL) return false;
            cur = cur->nxt[imap];
        }
        return cur->is_end;
    }
};