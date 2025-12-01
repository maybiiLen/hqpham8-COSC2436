class Solution {
public:
    string decodeString(string s) {
        stack<int> counts;
        stack<string> segments;
        string current;
        int number = 0;
        for (char c : s) {
            if (isdigit(c)) {
                number = number * 10 + (c - '0');
            } else if (c == '[') {
                counts.push(number);
                segments.push(current);
                number = 0;
                current.clear();
            } else if (c == ']') {
                int repeat = counts.top();
                counts.pop();
                string prev = segments.top();
                segments.pop();
                while (repeat--) {
                    prev += current;
                }
                current = prev;
            } else {
                current.push_back(c);
            }
        }
        return current;
    }
};

