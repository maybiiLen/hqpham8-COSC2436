class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& tmp) {
        stack<int> stk;
        int size = tmp.size();
        vector<int>answer(size);//declare array to put answer in
        for(int i = 0; i < size; i++){
            while(!stk.empty() && tmp[stk.top()] < tmp[i]){  // compare current indice to indice on top of stack
                answer[stk.top()] = i - stk.top(); //pass the differnce of the two indice into the stack
                stk.pop(); //after that pop the top of stack 
            }
            stk.push(i); //push current indice to top of stack so we can compare next indice to top of stack again
        }
        return answer; //return answer array 
    }
};

