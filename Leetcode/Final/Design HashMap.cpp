class MyHashMap {
    static constexpr int kBucketCount = 1021;
    vector<list<pair<int, int>>> buckets;

    int index(int key) const {
        return key % kBucketCount;
    }

public:
    MyHashMap() : buckets(kBucketCount) {}

    void put(int key, int value) {
        int idx = index(key);
        for (auto& entry : buckets[idx]) {
            if (entry.first == key) {
                entry.second = value;
                return;
            }
        }
        buckets[idx].emplace_back(key, value);
    }

    int get(int key) {
        int idx = index(key);
        for (auto& entry : buckets[idx]) {
            if (entry.first == key) {
                return entry.second;
            }
        }
        return -1;
    }

    void remove(int key) {
        int idx = index(key);
        for (auto it = buckets[idx].begin(); it != buckets[idx].end(); ++it) {
            if (it->first == key) {
                buckets[idx].erase(it);
                return;
            }
        }
    }
};

