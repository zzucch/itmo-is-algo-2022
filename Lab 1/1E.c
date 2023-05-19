#include <stdio.h>
#include <math.h>

int main() {
    int n;
    scanf("%d", &n);

    int a[n];
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }
    int x;
    scanf("%d", &x);

    int delta = 3000;
    int thatNum;
    for (int i = 0; i < n; ++i) {
        if (delta > abs(a[i] - x)) {
            delta = abs(a[i] - x);
            thatNum = a[i];
        }
    }
    printf("%d", thatNum);
    return 0;
}
