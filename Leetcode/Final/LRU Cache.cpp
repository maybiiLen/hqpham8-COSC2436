class LRUCache {
    int capacity;
    list<pair<int, int>> order;
    unordered_map<int, list<pair<int, int>>::iterator> positions;

    void moveToFront(list<pair<int, int>>::iterator it) {
        order.splice(order.begin(), order, it);
    }

public:
    LRUCache(int capacity) : capacity(capacity) {}

    int get(int key) {
        auto it = positions.find(key);
        if (it == positions.end()) {
            return -1;
        }
        moveToFront(it->second);
        return it->second->second;
    }

    void put(int key, int value) {
        auto it = positions.find(key);
        if (it != positions.end()) {
            it->second->second = value;
            moveToFront(it->second);
            return;
        }
        if (static_cast<int>(order.size()) == capacity) {
            auto remove = order.back();
            positions.erase(remove.first);
            order.pop_back();
        }
        order.emplace_front(key, value);
        positions[key] = order.begin();
    }
};

