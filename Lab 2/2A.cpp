#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;
    int array[n + 1];
    for (int i = 0; i < n; ++i) {
        cin >> array[i];
    }
    int newNum, newIndex;
    cin >> newNum >> newIndex;
    for (int i = n + 1; newIndex <= i; --i) {
        array[i] = array[i - 1];
    }
    array[newIndex - 1] = newNum;
    for (int i = 0; i < n + 1; ++i) {
        cout << array[i] << " ";
    }
    return 0;
}
