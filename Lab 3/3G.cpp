#include <iostream>
#include <iomanip>

double binarySearchMod(double a[], int n) {
    double lo = 0;
    double hi = 10000000000;

    while (hi > lo + 1e-9) {
        bool touchesGround = false;
        double mid = (lo + hi) / 2;

        a[1] = mid;

        for (int i = 2; i < n; ++i) {
            a[i] = 2 * a[i - 1] - a[i - 2] + 2;
            if (a[i] <= 0) {
                touchesGround = true;
                break;
            }
        }

        if (touchesGround) {
            lo = mid;
        } else {
            hi = mid;
        }
    }

    return hi;
}

int main() {
    int n;
    double A, B;

    std::cin >> n >> A;

    double lights[n];
    lights[0] = A;

    lights[1] = binarySearchMod(lights, n);

    for (int i = 2; i < n; ++i) {
        lights[i] = 2 * lights[i - 1] - lights[i - 2] + 2;
    }

    std::cout << std::fixed << std::setprecision(2) << lights[n - 1];
    return 0;
}
