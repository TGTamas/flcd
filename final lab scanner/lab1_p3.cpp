int n;
int a;
int b;
int i;

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

