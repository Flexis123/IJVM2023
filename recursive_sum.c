#include <stdio.h>

int sumem(int n) {
    if (n == 0) return 0;
    return n + sumem(n-1);
}

int main(){
    int num;
    scanf("%d", &num);
    printf("%d", sumem(num));
    return 0;
}