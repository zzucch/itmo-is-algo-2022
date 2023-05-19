#include <iostream>

struct Node {
    int value;
    Node *next;
    int *maxValue;
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

    void getMaxValue() {
        std::cout << *Head->maxValue << '\n';
    }

    void addNode(int newData) {
        Node *newNode = new Node;
        newNode->value = newData;

        if (isEmpty()) {
            Head = newNode;
            Tail = newNode;

            newNode->maxValue = &newNode->value;
            newNode->next = nullptr;
        } else {
            newNode->next = Head;
            Head = newNode;
            if (*newNode->next->maxValue < newData) {
                newNode->maxValue = &newNode->value;
            } else {
                newNode->maxValue = newNode->next->maxValue;
            }
        }

    }

    void excludeFirstNode() {
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
        } else if (command == 'm') {
            std::cin.ignore(2);
            stack.getMaxValue();
        } else {
            std::cin >> data;
            stack.addNode(data);
        }
    }

    std::cout << std::endl;
    return 0;
}
