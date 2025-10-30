class Solution {
public:
    int timeRequiredToBuy(vector<int>& tickets, int k) {
        queue<pair<int, int>> q;
        
        for (int i = 0; i < tickets.size(); i++) {
            q.push({tickets[i], i});
        }
        
        int time = 0;
        
        while (!q.empty()) {
            auto front = q.front();
            q.pop();
            
            time++;
            front.first--;
            
            if (front.second == k && front.first == 0) {
                return time;
            }
            
            if (front.first > 0) {
                q.push(front);
            }
        }
        
        return time;
    }
};