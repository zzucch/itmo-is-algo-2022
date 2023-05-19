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
        return (Tail == nullptr);
    }

    void addNode(int newData) {
        Node *newNode = new Node;
        newNode->value = newData;

        if (isEmpty()) {
            Head = newNode;
            Tail = newNode;

            newNode->next = nullptr;
        } else {
            newNode->next = Head;
            Head = newNode;
        }
    }

    void excludeFirstNode() {
        std::cout << Head->value << '\n';

        Head = Head->next;
    }
} stack;

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
            stack.excludeFirstNode();
        } else {
            std::cin >> data;
            stack.addNode(data);
        }
    }

    std::cout << std::endl;
    return 0;
}
