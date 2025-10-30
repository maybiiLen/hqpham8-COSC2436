class Solution {
public:
    int countStudents(vector<int>& students, vector<int>& sandwiches) {
        queue<int> q;
        for (int s : students) {
            q.push(s);
        }
        
        int sandwichIndex = 0;
        int attempts = 0;
        
        while (!q.empty() && sandwichIndex < sandwiches.size()) {
            if (q.front() == sandwiches[sandwichIndex]) {
                q.pop();
                sandwichIndex++;
                attempts = 0;
            } else {
                q.push(q.front());
                q.pop();
                attempts++;
            }
            
            if (attempts == q.size()) {
                break;
            }
        }
        
        return q.size();
    }
};