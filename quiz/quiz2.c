#include <stdio.h>
int main()
{
    int a = 1, b = 2, c = 3;
    int *ptr1 = &a;
    int **sptr = &ptr1;
    *sptr = &c;
    printf("%d\n", *ptr1 );
}
