#include "stdafx.h"

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

                // READ DOS HEADER 
                PIMAGE_DOS_HEADER dosHeader = (PIMAGE_DOS_HEADER)fileData;
                std::cout << "[*] Dos Header Info;" << std::endl;
                printf("[+] 0x%x\t : Magic Number(e_magic)\n", dosHeader->e_magic);
                printf("[+] 0x%x\t : File address of new exe header(e_lfanew)\n", dosHeader->e_lfanew);

                // READ IMAGE_NT_HEADERS
                std::cout << "[*] Image NT Headers Info;" << std::endl;
                PIMAGE_NT_HEADERS imageNTHeader = (PIMAGE_NT_HEADERS)((DWORD)fileData + dosHeader->e_lfanew);

                printf("[+] 0x%x\t : Signature\n", imageNTHeader->Signature);
                printf("[+] 0x%x\t : Time Date Stamp\n", imageNTHeader->FileHeader.TimeDateStamp);
                printf("[+] 0x%x\t : Size Of Optional Header\n", imageNTHeader->FileHeader.SizeOfOptionalHeader);
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