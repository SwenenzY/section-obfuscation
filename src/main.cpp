#include <Windows.h>
#include <iostream>
#include <filesystem>


int main(int argc,char* argv[])
{
    // have args
    if (argv[1]) {
        // file exits
        if (std::filesystem::exists(argv[1])) {
            std::cout << "[!] Working file : " << argv[1] << std::endl; // print
            HANDLE file = CreateFileA(argv[1], GENERIC_ALL, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
            if (file != INVALID_HANDLE_VALUE) {
                DWORD bytesRead = NULL;
                // allocate heap
                DWORD fileSize = GetFileSize(file, NULL);
                LPVOID fileData = HeapAlloc(GetProcessHeap(), 0, fileSize);
                // read file bytes to memory
                ReadFile(file, fileData, fileSize, &bytesRead, NULL);

                PIMAGE_DOS_HEADER dosHeader = (PIMAGE_DOS_HEADER)fileData;
                printf("[+] 0x%x\t : Magic Number\n", dosHeader->e_magic);



            }
            else {
                printf("[-] Failed to open specified file. (%d)\n", file);
            }
        } 
    }
    else {
        std::cout << "[-] File is not specified, please use this project.exe any.exe/.dll" << std::endl;
    }

    system("pause");
}