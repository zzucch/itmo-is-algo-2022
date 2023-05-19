#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    int a[n];
    for (int i = 0; i < n - 1; ++i) {
        scanf("%d", &a[i]);
    }

    int last;
    scanf("%d", &last);
    printf("%d ", last);

    for (int i = 0; i < n - 1; ++i) {
        printf("%d ", a[i]);
    }
    return 0;
}
