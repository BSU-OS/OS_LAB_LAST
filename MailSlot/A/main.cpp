#include <windows.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
std::ofstream output("TEST.txt");
HANDLE inputHSlot,outputHSlot;
LPCTSTR outputSlotName = TEXT("\\\\.\\mailslot\\INPUT");
LPCTSTR inputSlotName = TEXT("\\\\.\\mailslot\\OUTPUT");

BOOL WINAPI MakeSlot(LPCTSTR lpszSlotName) {

    inputHSlot = CreateMailslot(lpszSlotName,
                                0,                             // no maximum message size
                                MAILSLOT_WAIT_FOREVER,         // no time-out for operations
                                (LPSECURITY_ATTRIBUTES) NULL); // default security

    if (inputHSlot == INVALID_HANDLE_VALUE) {
        output << "CreateMailslot failed with " << GetLastError() << '\n';
        return FALSE;
    } else output << "Mailslot created successfully.\n";
    return TRUE;
}

void ReadData(std::string *data) {
    char buf[1024];
    DWORD NumberOfBytesRead;

    ReadFile(inputHSlot, (LPVOID) buf, sizeof(buf), &NumberOfBytesRead, NULL);
    *data = buf;
}

void WriteData(const std::string *data) {

    outputHSlot = CreateFile(outputSlotName,
                             GENERIC_WRITE,
                             FILE_SHARE_READ,
                             (LPSECURITY_ATTRIBUTES) NULL,
                             OPEN_EXISTING,
                             FILE_ATTRIBUTE_NORMAL,
                             (HANDLE) NULL);
    if (outputHSlot == INVALID_HANDLE_VALUE) {
        output<< "CreateFile failed with " <<  GetLastError() << '\n';
        return;
    }

    BOOL fResult;
    DWORD cbWritten;

    fResult = WriteFile(outputHSlot,
                        TEXT(data->c_str()),
                        (DWORD) (lstrlen(data->c_str()) + 1) * sizeof(TCHAR),
                        &cbWritten,
                        (LPOVERLAPPED) NULL);

    if (!fResult) {
        output << "WriteFile failed with " <<  GetLastError() << '\n';
        return;
    }

    output<< "Slot written to successfully.\n";
    CloseHandle(outputHSlot);
}

int main() {
    MakeSlot(inputSlotName);
    Sleep(1000);
    std::string inputData;
    //ReadData(&inputData);
    std::stringstream input(inputData);
    int x;
    std::string str = "1 2 31 3 1 14";
//    while (input >> x) {
//        str += std::to_string(x + 5);
//        str += ' ';
//    }

    WriteData(&str);

    output << inputData << "\nTested!!!";
    output.close();
    CloseHandle(inputHSlot);
}
