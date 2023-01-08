#include <iostream>
#include <string>
int main() {
    int x;
    std::string str = "";
    while (std::cin >> x) {
        str += std::to_string(x + 5);
        str += ' ';
    }
    std::cout << str;

}
