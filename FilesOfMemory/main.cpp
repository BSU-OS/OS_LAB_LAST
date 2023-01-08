
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>

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

std::string CalculateProcess(std::string ModuleName, const std::string data) {
    std::cout << "The receiving process: " << ModuleName << std::endl;
    STARTUPINFO si={sizeof si};
    si.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
    //скрываем окно дочернего процесса
    si.wShowWindow = SW_HIDE;
    //Создаём дочерний процесс
    PROCESS_INFORMATION pi;
    WriteFile(&data);
    CreateProcess(
            ModuleName.c_str(),
            NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &si,
            &pi
    );// здесь будут дескрипторы и идентификаторы нового процесса и его первичного потока
    WaitForSingleObject(pi.hProcess, INFINITE);
    std::cout << "Input data:   " << data << std::endl;
    //чтение данных
    std::string buf;
    ReadFile(&buf);
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