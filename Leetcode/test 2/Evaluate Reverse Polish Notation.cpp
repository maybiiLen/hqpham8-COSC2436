class Solution {
public:
    int evalRPN(vector<string>& tk) {
        stack<int>stk; 
        int size = tk.size();

        int answer = 0;

        for(int i = 0; i < size;i++){
            if(tk[i] != "+" && tk[i] != "-" && tk[i] != "*" && tk[i] != "/"){
                stk.push(stoi(tk[i]));
            }
            else if(tk[i] == "+"){
                int top1 = stk.top();
                stk.pop();
                int top2 = stk.top();
                stk.pop();

                answer = top1 + top2;
                stk.push(answer);
            }
            else if(tk[i] == "-"){
                int top1 = stk.top();
                stk.pop();
                int top2 = stk.top();
                stk.pop();

                answer = top2 - top1;
                stk.push(answer);
            }
            else if(tk[i] == "*"){
                int top1 = stk.top();
                stk.pop();
                int top2 = stk.top();
                stk.pop();

                answer = top2 * top1;
                stk.push(answer);
            }
            else if(tk[i] == "/"){
                int top1 = stk.top();
                stk.pop();
                int top2 = stk.top();
                stk.pop();

                answer = top2 / top1;
                stk.push(answer);
            }
        }
        return stk.top();

    }
};