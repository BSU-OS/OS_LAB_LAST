
#include <windows.h>
#include <iostream>
#include <string>

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

std::string CalculateProcess(std::string ModuleName, const std::string data) {
    std::cout << "The receiving process: " << ModuleName << std::endl;
    STARTUPINFO si = {sizeof si};
    si.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
    //скрываем окно дочернего процесса
    si.wShowWindow = SW_HIDE;
    //Создаём дочерний процесс
    PROCESS_INFORMATION pi;
    WriteData(&data);
    CreateProcess(
            ModuleName.c_str(),
            NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &si,
            &pi
    );// здесь будут дескрипторы и идентификаторы нового процесса и его первичного потока
    WaitForSingleObject(pi.hProcess, INFINITE);
    std::cout << "Input data:   " << data << std::endl;
    //чтение данных
    std::string buf;
    ReadData(&buf);
    std::cout << "Output data:  " << buf << std::endl;
    TerminateProcess(pi.hProcess, 0);//убиваем дочерний процесс
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return std::string(buf);
}

int main() {
    CalculateProcess("..\\A\\cmake-build-debug\\A.exe",
                     CalculateProcess("..\\B\\cmake-build-debug\\B.exe",
                                      CalculateProcess(
                                              "..\\A\\cmake-build-debug\\A.exe",
                                              "1 2 4 5 12 ")));
    return 0;
}