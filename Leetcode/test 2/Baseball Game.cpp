class Solution {
public:
    int calPoints(vector<string>& op) {
        stack<int> stk;
        int sum = 0;
        for(int i = 0; i < op.size(); i++){
            if(op[i] != "C" && op[i] != "D" && op[i] != "+"){
                stk.push(stoi(op[i]));
                sum = sum + stoi(op[i]);
            }
            else if(op[i] == "+"){
                int top1 = stk.top();
                stk.pop();

                int top2 = stk.top();
                stk.pop();
        
                int newScore = top1 + top2; 
                stk.push(top2);
                stk.push(top1);
                stk.push(newScore);
                sum = sum + newScore;
            }
            else if(op[i] == "D"){
                int top1 = stk.top();
                stk.pop();

                int newScore = top1 * 2; 
                stk.push(top1);
                stk.push(newScore);
                sum = sum + newScore;
            }
            else if(op[i] == "C"){
                int removed = stk.top();
                stk.pop();
                sum = sum - removed;
            }
        }
        return sum; 
    }
};