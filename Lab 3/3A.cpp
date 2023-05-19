#include <iostream>

struct Node {
    int value;
    Node *next;
};

struct List {
    Node *Head;
    Node *Tail;

    List() {
        Head = nullptr;
        Tail = nullptr;
    }

    bool isEmpty() {
        return (Head == nullptr);
    }

    void addNode(int newData) {
        Node *newNode = new Node;
        newNode->value = newData;

        newNode->next = nullptr;

        if (isEmpty()) {
            Head = newNode;
            Tail = newNode;
        } else {
            Tail->next = newNode;
            Tail = newNode;
        }
    }

    void excludeNode() {
        std::cout << Head->value << '\n';

        Head = Head->next;
    }
} queue;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    for (int i = 0; i < n; ++i) {
        int data;
        char command;

        std::cin >> command;

        if (command == '-') {
            queue.excludeNode();
        } else {
            std::cin >> data;
            queue.addNode(data);
        }
    }

    std::cout << std::endl;
    return 0;
}
