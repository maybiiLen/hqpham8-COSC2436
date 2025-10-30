class Solution {
public:
    int maxDepth(string s) {
        int current = 0;
        int maxD = 0;
        
        for (char c : s) {
            if (c == '(') {
                current++;
                maxD = max(maxD, current);
            } else if (c == ')') {
                current--;
            }
        }
        
        return maxD;
    }
};