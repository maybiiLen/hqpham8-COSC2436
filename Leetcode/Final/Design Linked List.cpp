class MyLinkedList {
    struct Node {
        int val;
        Node* next;
        Node(int v) : val(v), next(nullptr) {}
    };

    Node* head;
    int size;

    Node* getNode(int index) {
        Node* curr = head;
        while (index-- && curr) {
            curr = curr->next;
        }
        return curr;
    }

public:
    MyLinkedList() : head(nullptr), size(0) {}

    int get(int index) {
        if (index < 0 || index >= size) {
            return -1;
        }
        return getNode(index)->val;
    }

    void addAtHead(int val) {
        Node* node = new Node(val);
        node->next = head;
        head = node;
        ++size;
    }

    void addAtTail(int val) {
        Node* node = new Node(val);
        if (!head) {
            head = node;
        } else {
            Node* tail = getNode(size - 1);
            tail->next = node;
        }
        ++size;
    }

    void addAtIndex(int index, int val) {
        if (index < 0 || index > size) {
            return;
        }
        if (index == 0) {
            addAtHead(val);
            return;
        }
        Node* prev = getNode(index - 1);
        Node* node = new Node(val);
        node->next = prev->next;
        prev->next = node;
        ++size;
    }

    void deleteAtIndex(int index) {
        if (index < 0 || index >= size) {
            return;
        }
        if (index == 0) {
            Node* temp = head;
            head = head->next;
            delete temp;
        } else {
            Node* prev = getNode(index - 1);
            Node* temp = prev->next;
            prev->next = temp->next;
            delete temp;
        }
        --size;
    }
};

