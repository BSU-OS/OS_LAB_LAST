#include <windows.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

void ReadData(std::string *data) {
    OpenClipboard(nullptr);

    HANDLE hData = GetClipboardData(CF_TEXT);

    char *pszText = static_cast<char *>(GlobalLock(hData));

    *data = pszText;

    GlobalUnlock(hData);

    CloseClipboard();

}

void WriteData(const std::string *data) {
    OpenClipboard(nullptr);
    HGLOBAL clipbuffer;
    char *buffer;
    EmptyClipboard();
    clipbuffer = GlobalAlloc(GMEM_DDESHARE, data->length() + 1);
    buffer = (char *) GlobalLock(clipbuffer);
    strcpy(buffer, data->c_str());
    GlobalUnlock(clipbuffer);
    SetClipboardData(CF_TEXT, clipbuffer);
    CloseClipboard();
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
    std::ofstream output("TEST.txt");
    output << inputData << "\nTested!!!";
    output.close();
}
