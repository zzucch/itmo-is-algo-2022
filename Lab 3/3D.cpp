#include <iostream>

struct Node {
    int value;
    Node *next;
};

struct List {
    Node *Head;

    List() {
        Head = nullptr;
    }

    bool isEmpty() {
        return (Head == nullptr);
    }

    void addNode(int newData) {
        Node *newNode = new Node;
        newNode->value = newData;

        newNode->next = Head;
        Head = newNode;
    }

    void excludeFirstNode() {
        Head = Head->next;
    }
} stack;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    char s;

    while (std::cin >> s) {
        if (s == '+') {
            stack.Head->next->value += stack.Head->value;
            stack.excludeFirstNode();
        } else if (s == '-') {
            stack.Head->next->value -= stack.Head->value;
            stack.excludeFirstNode();
        } else if (s == '*') {
            stack.Head->next->value *= stack.Head->value;
            stack.excludeFirstNode();
        } else {
            stack.addNode((int) s - 48);
        }
    }

    std::cout << stack.Head->value << std::endl;
    return 0;
}
