#include <iostream>

int main() {
    int a, b;

    std::cout << std::fixed;
    std::cout.precision(9);

    std::cin >> a >> b;
    std::cout << (double)a / b << "\n";

    return 0;
}