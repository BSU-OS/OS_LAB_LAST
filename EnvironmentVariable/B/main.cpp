#include <windows.h>
#include <iostream>
#include <string>
#include <sstream>

const std::string BUFFER_VARIABLE = "BUFFER_VARIABLE";

void ReadData(std::string *data) {
    char buf[1024];
    GetEnvironmentVariable(BUFFER_VARIABLE.c_str(), buf, sizeof(buf));
    *data = buf;
}

void WriteData(const std::string *data) {
    SetEnvironmentVariable(BUFFER_VARIABLE.c_str(), data->c_str());
}

int main() {
    std::string inputData;
    ReadData(&inputData);
    std::stringstream input(inputData);
    int x;
    std::string str = "";
    while (input >> x) {
        str += std::to_string(3 * x);
        str += ' ';
    }
    WriteData(&str);
}
