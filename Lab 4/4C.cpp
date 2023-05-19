#include <iostream>
#include <vector>

struct object {
    int value;
    int position;
};

void siftUp(std::vector<object> &a, unsigned long long i) {
    while (i != 0 && a[i].value < a[(i - 1) / 2].value) {
        std::swap(a[i], a[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void siftDown(std::vector<object> &a, int i) {
    while (2 * i + 1 < a.size()) {
        int l = 2 * i + 1;
        int r = 2 * i + 2;

        int j = l;
        if (r < a.size() && a[r].value < a[l].value) {
            j = r;
        }
        if (a[i].value <= a[j].value) {
            break;
        }
        std::swap(a[i], a[j]);
        i = j;
    }
}

void push(std::vector<object> &a, int data, int count) {
    object newObject{};
    newObject.value = data;
    newObject.position = count;
    a.push_back(newObject);

    siftUp(a, a.size() - 1);
}

void extractMin(std::vector<object> &a) {
    if (a.empty()) {
        std::cout << "*\n";
    } else {
        int min = a.front().value;
        a[0] = a[a.size() - 1];
        a.pop_back();
        siftDown(a, 0);

        std::cout << min << '\n';
    }
}

void decreaseKey(std::vector<object> &a, int x, int y) {
    for (int i = 0; i < a.size(); ++i) {
        if (a[i].position == x) {
            a[i].value = y;
            siftUp(a, i);
            break;
        }
    }

}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string operation;
    std::vector<object> queue;
    int count = 0;
    int data = 0;

    while (std::cin >> operation) {
        ++count;
        if (operation == "push") {
            std::cin >> data;

            push(queue, data, count);
        } else if (operation == "extract-min") {
            extractMin(queue);
        } else if (operation == "decrease-key") {
            int x, y;
            std::cin >> x >> y;

            decreaseKey(queue, x, y);
        }
    }

    return 0;
}
