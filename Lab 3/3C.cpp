#include <iostream>

struct Node {
    char value;
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

    void addNode(char newData) {
        Node *newNode = new Node;
        newNode->value = newData;

        newNode->next = Head;
        Head = newNode;
    }

    void removeNode() {
        Head = Head->next;
    }
} stack;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string str;

    while (std::cin >> str) {
        bool result = true;

        for (char i : str) {
            if (stack.isEmpty()) {
                if (i == '(' || i == '[') {
                    stack.addNode(i);
                } else {
                    result = false;
                }
            } else if (i == ')') {
                if (stack.Head->value == '(') {
                    stack.removeNode();
                } else {
                    result = false;
                }
            } else if (i == ']') {
                if (stack.Head->value == '[') {
                    stack.removeNode();
                } else {
                    result = false;
                }
            } else {
                stack.addNode(i);
            }
        }
        if (!(stack.isEmpty())) {
            result = false;
            while (stack.Head->next != nullptr) {
                stack.Head = stack.Head->next;
            }
            stack.Head = nullptr;
        }
        std::cout << (result ? "YES" : "NO") << '\n';
    }

    std::cout << std::endl;
    return 0;
}
