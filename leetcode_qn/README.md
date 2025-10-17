## 3680. Generate Schedule
https://leetcode.com/problems/generate-schedule/description/
https://leetcode.com/problems/generate-schedule/solutions/7186393/easy-solution-keep-adding-teams/
if not res or ind1 not in res[-1] and ind2 not in res[-1] and tuple([ind1,ind2]) not in res_s:
not res: if res is empty, add pair to set.
ind1 not in res[-1] and ind2 not in res[-1]: check new pair does not have same as last pair
tuple([ind1,ind2]) not in res_s: check pair is not used b4.
for i in range(0, 2*(n+1)) is crucial. Changing it to n will create wrong ans for n=5. Changing it to 2*n will create wrong ans for n=6.
Greedy algorithm. O(N^2).
Tried to traverse matrix with loopback greedily results in wrong ans. Tried dfs results in TLE for n=6.

## 3690. Split and Merge Array Transformation
https://leetcode.com/problems/split-and-merge-array-transformation/description/
constraint 6. BFS. set to avoid revisiting.
Short code:
C++: https://leetcode.com/problems/split-and-merge-array-transformation/solutions/7210528/simple-bfs-explanation-with-added-video-explanation/
Python: https://leetcode.com/problems/split-and-merge-array-transformation/solutions/7209653/just-combination-of-bfs-and-permutations-brute-force/

## 3691. Maximum Total Subarray Value II
https://leetcode.com/problems/maximum-total-subarray-value-ii/description/
no RMQ: https://leetcode.com/problems/maximum-total-subarray-value-ii/solutions/7210224/divide-and-conquer-no-rmq/
RMQ: https://leetcode.com/problems/maximum-total-subarray-value-ii/solutions/7209652/solution-with-constraint-k-n-n-1-2/
Beat 100%: https://leetcode.com/problems/maximum-total-subarray-value-ii/solutions/7210456/beats-100-simple-solution-using-max-heap-and-sparse-table/
RMQ Sparse table: https://leetcode.com/problems/maximum-total-subarray-value-ii/solutions/7211061/rmq-sparse-table-heap-for-maximum/
SQRT decomp: https://leetcode.com/problems/maximum-total-subarray-value-ii/solutions/7213409/square-root-decomposition-solution/

## 3713. Longest Balanced Substring I
This problem is brute force O(N^2*26).
Using set to insert cause TLE. Using simple logic to compare freq does not cause TLE.
This is due to std::set:
- allocates memory dynamically on every insertion,
- incurs rebalancing cost (O(log n)),
- and involves hashing or tree node overhead (cache-unfriendly).

By switching to simple scalar comparison, you eliminated:
- all heap allocations,
- all branching inside the set,
- all hashing/rebalancing,
- and improved cache locality.
So now the inner loop is pure arithmetic and very CPU-cache-friendly — making it hundreds of times faster in practice even though big-O is the same.

## 3714. Longest Balanced Substring II
This problem is about pattern matching using map and invariant. O(N) algo
Referred solution: https://leetcode.com/problems/longest-balanced-substring-ii/solutions/7268216/python-prefix-sum/

Own implementation in C++:
Can get TLE if using map due to log N for count() and insert() operation.
Using tuple prevents us from using unordered_map.
Use unordered_map with integer key.
Cannot do unordered_map with tuple. Convert the tuple to a long long using some function (1-1).
Python dict is faster than C++ unordered_map. python dict uses open-address (with perturbation probing) hash table (cached, contiguous slot cache-friendly) whereas C++ uses hash table with chaining (cache miss)

Another way to formulate the soln is to solve it considering 3 cases. Case 1: single letter. Case 2: 2 letters same freq (unordered_map<int, int>). Case 3: 3 letters same freq (map<pair<int,int>, int>). This formulation has a better runtime.