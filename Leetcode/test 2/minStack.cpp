class MinStack {
private:
    stack<int> mainStk;
    stack<int> minStk;
public:
    MinStack() {
        
    }
    
    void push(int val) {
        mainStk.push(val); // When we push a value into mainStk, we also consider if it should go into minStk


        //if min stackis empty or is less than or equal to val 
        if(minStk.empty() || val <= minStk.top()){
            minStk.push(val); //min stack always keep track of minimuim on top 
        } //for example if we have value [5, 2 , 3 , 9 ,8]
    } // main stack pusheh [botton- 5, 2 , 3, 9, 8 top]
     // min stack pushes [bottom - 5, 2 top] since every value that comes after 2 that is getting push isnt less than the top of the stack which is 2, we dont push 3 9 8. thiis mean the top of the stack is awlays going to be 2 for this case.
    
    void pop() {
       if(mainStk.top() == minStk.top()){
        minStk.pop();
       }
       mainStk.pop();
    }
    
    int top() {
        return mainStk.top();
    }
    
    int getMin() {
        return minStk.top();  // this simply mean we can just return the top of the stack and get min, O(1) solution since we directly get the value and dont have to traverse anything
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */