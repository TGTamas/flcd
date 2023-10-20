#include <iostream>

int a;
int b;
int c;
int d;

int main()
{
    //MIN OF 3 NUMBERS

    std::cin >> a;
    std::cin >> b;
    std::cin >> c;

    if (a < b)
        d = a;
    else
        d = b;

    if (c < d)
        d = c;

    std::cout << d;
}
