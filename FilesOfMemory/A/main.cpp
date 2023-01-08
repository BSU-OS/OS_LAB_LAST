#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

const std::string BUF_PATH = "..\\data.txt";

void ReadFile(std::string *data) {
    std::ifstream input(BUF_PATH, std::ios_base::in);
    *data = std::string{std::istreambuf_iterator<char>(input), std::istreambuf_iterator<char>()};
    input.close();
}

void WriteFile(const std::string *data) {
    std::ofstream ouput(BUF_PATH, std::ios_base::out);
    ouput << *data;
    ouput.close();
}

int main() {
    std::string inputData;
    ReadFile(&inputData);
    std::stringstream input(inputData);
    int x;
    std::string str = "";
    while (input >> x) {
        str += std::to_string(x + 5);
        str += ' ';
    }
    WriteFile(&str);
}
