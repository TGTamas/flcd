#include <iostream>

int n;
it a; //LEXICAL ERROR
int 1b; //LEXICAL ERROR
int i;

int main()
{
    //SUM OF N NUMBERS

    b = 0;

    std::cin >> n;

    int numbers[10];

    for (i = 0; i < n; i++)
    {
        std::cin >> a;
        numbers[i] = a;
        b += a;
    }

    std::cout << b;
}
