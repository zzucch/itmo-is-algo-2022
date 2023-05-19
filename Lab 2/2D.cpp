#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;
    int array[n];
    for (int i = 0; i < n; ++i) {
        cin >> array[i];
    }
    for (int i = 1; i < n; ++i) {
        int j = i, key = array[i];
        while (key < array[j - 1] && j > 0) {
            array[j] = array[j - 1];
            --j;
        }
        array[j] = key;
        if (j < i) {
            for (int k = 0; k < n; ++k) {
                cout << array[k] << " ";
            }
            cout << endl;
        }
    }
    return 0;
}
