#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

//this uses backtracking (DFS)
class word_search{

    bool findLetterOfWord(string word, int word_idx, vector<vector<char>>& board, int row, int col, vector<vector<bool>>& visited){
        //finish finding the word
        if(word_idx>=word.size()){
            return true;
        }
        
        //went out of board
        if(row>=board.size() || row<0){
            return false;
        }
        if(col>=board[0].size() || col<0){
            return false;
        }
        
        if(visited[row][col]){ //cannot use letter cell more than once.
            return false;
        }
        if(board[row][col]==word[word_idx]) //find the next word
        {
            visited[row][col]=true;
            //cout<<row<<", "<<col<<endl;
            bool ret=findLetterOfWord(word, word_idx+1, board, row+1, col, visited);
            if(ret){
                return true;
            }
            ret = findLetterOfWord(word, word_idx+1, board, row-1, col, visited);
            if(ret){
                return true;
            }
            ret = findLetterOfWord(word, word_idx+1, board, row, col+1, visited);
            if(ret){
                return true;
            }
            ret=findLetterOfWord(word, word_idx+1, board, row, col-1, visited);
            if(ret){
                return true;
            }
            visited[row][col]=false; //backtracking
            return false;
        }
    }

    //this wil find 1 word in the board
    bool findWordInBoard(vector<vector<char>> board, string word){
        int m=board.size();
        int n=board[0].size();
        
        for(int row=0;row<m;row++){
            for(int col=0;col<n;col++){
                vector<vector<bool>> visited(m, vector<bool>(n,false));
                bool find_word=findLetterOfWord(word, 0, board, row, col, visited);
                if(find_word){
                    return true;
                }
            }
        }
        return false;
    }

    void printBoard(vector<vector<char>>& board){
        int m=board.size();
        int n=board[0].size();
        
        for(int row=0;row<m;row++){
            for(int col=0;col<n;col++){
                printf("%c, ", board[row][col]);
            }
            printf("\n");
        }
        printf("\n");
    }

    void printWordsList(vector<string>& words){
        for(int i=0;i<words.size();i++){
            printf("%s\n", words[i].c_str());
        }
    }

    //this will find the words list in a board
    vector<string> findWords(vector<vector<char>> board, vector<string> words) {
        
        //printBoard(board);
        //printWordsList(words);
        vector<string> ret;
        for(int i=0;i<words.size();i++){
            string word=words[i];
            bool find_word=findWordInBoard(board, word);
            if(find_word){
                ret.push_back(word);
            }
        }
        
        sort(ret.begin(), ret.end());
        
        return ret;
    }
}