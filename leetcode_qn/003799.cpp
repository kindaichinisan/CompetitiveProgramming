// 3799. Word Squares II

// You are given a string array words, consisting of distinct 4-letter strings, each containing lowercase English letters.

// A word square consists of 4 distinct words: top, left, right and bottom, arranged as follows:

// top forms the top row.
// bottom forms the bottom row.
// left forms the left column (top to bottom).
// right forms the right column (top to bottom).
// It must satisfy:

// top[0] == left[0], top[3] == right[0]
// bottom[0] == left[3], bottom[3] == right[3]
// Return all valid distinct word squares, sorted in ascending lexicographic order by the 4-tuple (top, left, right, bottom)​​​​​​​.

 

// Example 1:

// Input: words = ["able","area","echo","also"]

// Output: [["able","area","echo","also"],["area","able","also","echo"]]

// Explanation:

// There are exactly two valid 4-word squares that satisfy all corner constraints:

// "able" (top), "area" (left), "echo" (right), "also" (bottom)
// top[0] == left[0] == 'a'
// top[3] == right[0] == 'e'
// bottom[0] == left[3] == 'a'
// bottom[3] == right[3] == 'o'
// "area" (top), "able" (left), "also" (right), "echo" (bottom)
// All corner constraints are satisfied.
// Thus, the answer is [["able","area","echo","also"],["area","able","also","echo"]].

// Example 2:

// Input: words = ["code","cafe","eden","edge"]

// Output: []

// Explanation:

// No combination of four words satisfies all four corner constraints. Thus, the answer is empty array [].

 

// Constraints:

// 4 <= words.length <= 15
// words[i].length == 4
// words[i] consists of only lowercase English letters.
// All words[i] are distinct.

// https://leetcode.com/problems/word-squares-ii/

class Solution {
public:
    vector<vector<string>> wordSquares(vector<string>& words) {
        int n=words.size();

        sort(words.begin(), words.end());

        for(int i=0;i<n;i++){
            cout<<words[i]<<" ";
        }
        cout<<endl;

        vector<vector<string>> ret;
        
        for(int i=0;i<n;i++){

            vector<string> temp;
            vector<bool> temp2(n, false);

            //first word in top
            cout<<"top: "<<words[i]<<endl;
            temp.push_back(words[i]);
            temp2[i]=true;
            
            for(int j=0;j<n;j++){
                //second word in left
                if(temp2[j]){
                    continue;
                }

                if(words[i][0]==words[j][0]){
                    
                    cout<<"left: "<<words[j]<<endl;
                    temp.push_back(words[j]);
                    temp2[j]=true;

                    for(int k=0;k<n;k++){
                        //third word in right
                        if(temp2[k]){
                            continue;
                        }
    
                        if(words[i][3]==words[k][0]){
                            
                            cout<<"right: "<<words[k]<<endl;
                            temp.push_back(words[k]);
                            temp2[k]=true;

                            for(int l=0;l<n;l++){
                                //fourth word in bot
                                if(temp2[l]){
                                    continue;
                                }
                                if(words[l][0]==words[j][3] && words[l][3]==words[k][3]){
                                    
                                    cout<<"bot: "<<words[l]<<endl;
                                    temp.push_back(words[l]);
                                    temp2[l]=true;
                                    ret.push_back(temp);

                                    temp.pop_back();
                                    temp2[l]=false;
                                }

                                
                            }
                            temp.pop_back();
                            temp2[k]=false;
                        }
    
                        
                    }

                    temp.pop_back();
                    temp2[j]=false;
                }

                
            }
            temp.pop_back();
            temp2[i]=false;
        }

        return ret;
    }
};