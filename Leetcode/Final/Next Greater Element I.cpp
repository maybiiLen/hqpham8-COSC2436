class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> nextGreater;
        stack<int> mono;
        for (int value : nums2) {
            while (!mono.empty() && mono.top() < value) {
                nextGreater[mono.top()] = value;
                mono.pop();
            }
            mono.push(value);
        }
        while (!mono.empty()) {
            nextGreater[mono.top()] = -1;
            mono.pop();
        }
        vector<int> result;
        result.reserve(nums1.size());
        for (int value : nums1) {
            result.push_back(nextGreater[value]);
        }
        return result;
    }
};

