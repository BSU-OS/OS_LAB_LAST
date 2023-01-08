
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <string>

HANDLE inputHSlot,outputHSlot;
LPCTSTR outputSlotName = TEXT("\\\\.\\mailslot\\OUTPUT");
LPCTSTR inputSlotName = TEXT("\\\\.\\mailslot\\INPUT");

BOOL WINAPI MakeSlot(LPCTSTR lpszSlotName) {

    inputHSlot = CreateMailslot(lpszSlotName,
                                0,                             // no maximum message size
                                 MAILSLOT_WAIT_FOREVER,         // no time-out for operations
                                 (LPSECURITY_ATTRIBUTES) NULL); // default security

    if (inputHSlot == INVALID_HANDLE_VALUE) {
        printf("CreateMailslot failed with %d\n", GetLastError());
        return FALSE;
    } else printf("Mailslot created successfully.\n");
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
        printf("CreateFile failed with %d.\n", GetLastError());
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
        printf("WriteFile failed with %d.\n", GetLastError());
        return;
    }

    printf("Slot written to successfully.\n");
    CloseHandle(outputHSlot);
}

std::string CalculateProcess(std::string ModuleName, const std::string data) {
    //MakeSlot(inputSlotName);
    std::cout << "The receiving process: " << ModuleName << std::endl;
    STARTUPINFO si = {sizeof si};
    si.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
    //скрываем окно дочернего процесса
    si.wShowWindow = SW_HIDE;
    //Создаём дочерний процесс
    PROCESS_INFORMATION pi = {0};
//WriteData(&data);
    CreateProcess(
            ModuleName.c_str(),
            NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &si,
            &pi
    );// здесь будут дескрипторы и идентификаторы нового процесса и его первичного потока

    WaitForSingleObject(pi.hProcess, INFINITE);
    std::cout << "Input data:   " << data << std::endl;
    //чтение данных
    std::string buf;
    //ReadData(&buf);
    std::cout << "Output data:  " << buf << std::endl;
    TerminateProcess(pi.hProcess, 0);//убиваем дочерний процесс
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    //CloseHandle(inputHSlot);//Close MailSlot
    return std::string(buf);
}

int main() {

//    CalculateProcess("..\\A\\cmake-build-debug\\A.exe",
//                     CalculateProcess("..\\B\\cmake-build-debug\\B.exe",
//                                      CalculateProcess(
//                                              "..\\A\\cmake-build-debug\\A.exe",
//                                              "1 2 4 5 12 ")));
    CalculateProcess("..\\A\\cmale-build-debug\\A.exe", "1 2 4 5 12");

    return 0;
}