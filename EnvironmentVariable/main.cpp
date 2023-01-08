
#include <windows.h>
#include <iostream>
#include <string>

const std::string BUFFER_VARIABLE = "BUFFER_VARIABLE";

void ReadData(std::string *data) {
    char buf[1024];
    GetEnvironmentVariable(BUFFER_VARIABLE.c_str(), buf, sizeof(buf));
    *data = buf;
}

void WriteData(const std::string *data) {
    SetEnvironmentVariable(BUFFER_VARIABLE.c_str(), data->c_str());
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
    putenv(BUFFER_VARIABLE.c_str());
    return 0;
}