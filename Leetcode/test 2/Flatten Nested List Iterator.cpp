class NestedIterator {
public:
    vector<int> flattened;
    int index;
    
    void flatten(vector<NestedInteger>& nestedList) {
        for (auto& ni : nestedList) {
            if (ni.isInteger()) {
                flattened.push_back(ni.getInteger());
            } else {
                flatten(ni.getList());
            }
        }
    }
    
    NestedIterator(vector<NestedInteger>& nestedList) {
        index = 0;
        flatten(nestedList);
    }
    
    int next() {
        return flattened[index++];
    }
    
    bool hasNext() {
        return index < flattened.size();
    }
};