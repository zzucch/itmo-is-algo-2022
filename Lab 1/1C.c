#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    int a[n];
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }
    int st = 2000000005;
    int nd = 2000000001;
    for (int i = 0; i < n; ++i) {
        if (a[i] < nd && a[i] < st) {
            nd = st;
            st = a[i];
        } else if (a[i] < nd && a[i] >= st){
            nd = a[i];
        }
    }
    printf("%d %d", st, nd);
    return 0;
}
