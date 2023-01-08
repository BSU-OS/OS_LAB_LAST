
#include <windows.h>
#include <iostream>

struct ProcessInfo {
    HANDLE input, output;
};

std::string CalculateProcess(std::string ModuleName, std::string data) {
    std::cout << "The receiving process: " << ModuleName << std::endl;
    SECURITY_ATTRIBUTES sa;//атрибуты защиты канала
    sa.lpSecurityDescriptor = NULL; //защита по умолчанию
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.bInheritHandle = true;//разрешаем наследование дескрипторов

    //обработка ошибок
    SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOOPENFILEERRORBOX | SEM_NOALIGNMENTFAULTEXCEPT);
    //Потоки
    ProcessInfo M, Parent;
    //дескрипторы пайпов
    //создаем анонимные каналы
    CreatePipe(&Parent.output, &M.input, &sa, 0); //канал для stdin дочернего процесса
    CreatePipe(&M.output, &Parent.input, &sa, 0); //канал для stdout дочернего процесса

    STARTUPINFO si;
    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE;//скрываем окно дочернего процесса
    //подменяем дескрипторы
    si.hStdOutput = Parent.input;
    si.hStdError = Parent.input;
    si.hStdInput = Parent.output;

    //Создаём дочерний процесс
    PROCESS_INFORMATION pi;

    CreateProcess(ModuleName.c_str(), NULL, NULL, NULL, TRUE, ABOVE_NORMAL_PRIORITY_CLASS, NULL, NULL, &si,
                  &pi);                // здесь будут дескрипторы и идентификаторы нового процесса и его первичного потока
    DWORD num = 1024;//количество переданых/прочитаных байт
    char buf[1024] = {};//буфер для чтения данных
    int sz = data.size();

    //передача данных
    WriteFile(M.input, data.c_str(), sz + 1, &num, NULL);
    std::cout << "Input data:   " << data << std::endl;
    CloseHandle(M.input);//закрываем канал stdin дочернего процесса

    //чтение данных
    ReadFile(M.output, buf, 1023, &num, NULL);
    std::cout << "Output data:  " << buf << std::endl;
    CloseHandle(Parent.output);//закрываем родительский принимающий пайп

    CloseHandle(Parent.input);
    CloseHandle(M.output);
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