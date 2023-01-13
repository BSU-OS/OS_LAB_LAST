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
    std::string inputData="";
    system("pause");
    ReadData(&inputData);
    std::cout << inputData << '\n';
    inputData="Hi from client\n";
    WriteData(&inputData);
    system("pause");
}