
#include <windows.h>
#include <iostream>
#include <string>


void ReadData(std::string *data) {
    LPCTSTR lpszString = "";
    COPYDATASTRUCT cds;
    cds.dwData = 1; // can be anything
    cds.cbData = sizeof(TCHAR) * (_tcslen(lpszString) + 1);
    cds.lpData=lpszString;
    SendMessage(hwnd, WM_COPYDATA, (WPARAM)hwnd, (LPARAM)(LPVOID)&cds);
}

void WriteData(const std::string *data) {
    COPYDATASTRUCT* pcds = (COPYDATASTRUCT*)lParam;
    if (pcds->dwData == 1)
    {
        LPCTSTR lpszString = (LPCTSTR)(pcds->lpData);
        *data=lpszString;
    }
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
//    CreateProcess(
//            ModuleName.c_str(),
//            NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &si,
//            &pi
//    );// здесь будут дескрипторы и идентификаторы нового процесса и его первичного потока
//    WaitForSingleObject(pi.hProcess, INFINITE);
    std::cout << "Input data:   " << data << std::endl;
    //чтение данных
    std::string buf;
    ReadData(&buf);
    std::cout << "Output data:  " << buf << std::endl;
//    TerminateProcess(pi.hProcess, 0);//убиваем дочерний процесс
//    CloseHandle(pi.hProcess);
//    CloseHandle(pi.hThread);
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