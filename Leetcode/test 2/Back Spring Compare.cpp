class Solution {
public:
    bool backspaceCompare(string s, string t) {
        stack<char>stk;
        stack<char>stk2;
        string a = "";
        string b = "";

        for(char c : s){
            if(c != '#'){
                stk.push(c);
            }
            else if(!stk.empty()){
                stk.pop();
            }
        }
        for(char c : t){
            if(c != '#'){
                stk2.push(c);
            }
            else if(!stk2.empty()){
                stk2.pop();
            }
        }
        while(!stk.empty()){
            a = a + stk.top();
            stk.pop();
        }
        while(!stk2.empty()){
            b = b + stk2.top();
            stk2.pop();
        }

        return a==b;
    }
};