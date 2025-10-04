// Ghost
// You are given a list of strings dictionary and are playing a game called Ghost. Ghost is a two-person word game where players alternate appending letters to a string. The string being made must be a valid prefix of a word in the dictionary, and the first person who spells out any word in the dictionary loses.

// Return whether the first player would win if both players are playing optimally.

// Constraints

// n ≤ 10,000 where n is the length of dictionary.

// m ≤ 50 where m is the max length of a string in dictionary


// Example:

// Input

// words = ["ghost", "ghostbuster", "gas"]
// Output

// false
// Explanation

// Here is a sample game when dictionary is ["ghost", "ghostbuster", "gas"]:

// Player 1: "g"

// Player 2: "h"

// Player 1: "o"

// Player 2: "s"

// Player 1: "t" [loses]

// If player 2 had chosen "a" as the second letter, player 1 would still lose since they'd be forced to write the last letter

#include<bits/stdc++.h>
using namespace std;

//assume only 'a' to 'z'
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
    bool win=false;
    
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
        
        if(!win){
            if(cur->level%2==0){
                win=true;
            }
        }
    }

    // O(|s|)
    // bool search(string s) {
    //     node *cur = root;
    //     for (int i = 0; i < s.size(); i++) {
    //         int imap = s[i] - 'a';
    //         if (cur->nxt[imap] == NULL) return false;
    //         cur = cur->nxt[imap];
    //     }
    //     return cur->is_end;
    // }
};

bool solve( vector<string> words ){
    Trie_string t;
    
    for(int i=0;i<words.size();i++){
         t.insert(words[i]);
         if(t.win){
             return true;
         }
     }
    return false;
}