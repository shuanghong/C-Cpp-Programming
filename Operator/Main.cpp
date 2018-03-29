#include <cstdio>

void LogicalOperatorShortCircuit(void)
{
    int a = 1, b = 1, c = 2, d = 3;

    if ((a == b) || (b == c) && (c > d))
    {
        printf("a = %d, b = %d\n", a, b);
    }
    else 
        printf("c = %d, d = %d\n", c, d);
}


void OperatorPriority(void)
{
    int a = 1, b = 2;

    int t = 1;

    int val1 = a + t ? a : b;
    int val2 = a + (t ? a : b);

    printf("val1 = %d, val2 = %d\n", val1, val2);
}

int main(int argc, char* argv[])
{
    LogicalOperatorShortCircuit();

    OperatorPriority();

    return 0;
}

