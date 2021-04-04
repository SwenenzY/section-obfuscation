#include "stdafx.h"
/*
    TODO ADD BLACKLIST SECTIONS
    CHECK SECTION VALID
*/

const char blacklist[] = {
    "INIT"
};


int main(int argc,char* argv[])
{
    // have args
    if (argv[1]) {
        // file exits
        if (std::filesystem::exists(argv[1])) {

            std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

            std::cout << "[!] Working file : " << argv[1] << std::endl; // print
            HANDLE file = CreateFileA(argv[1], GENERIC_ALL, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
            if (file != INVALID_HANDLE_VALUE) {
                DWORD fileSize = GetFileSize(file, NULL);
                BYTE* pByte = new BYTE[fileSize];
                DWORD dw;
                ReadFile(file, pByte, fileSize, &dw, NULL);

                PIMAGE_DOS_HEADER dos = (PIMAGE_DOS_HEADER)pByte;
                if (dos->e_magic != IMAGE_DOS_SIGNATURE)
                    return false;
                PIMAGE_FILE_HEADER FH = (PIMAGE_FILE_HEADER)(pByte + dos->e_lfanew + sizeof(DWORD));
                PIMAGE_OPTIONAL_HEADER OH = (PIMAGE_OPTIONAL_HEADER)(pByte + dos->e_lfanew + sizeof(DWORD) + sizeof(IMAGE_FILE_HEADER));
                PIMAGE_SECTION_HEADER SH = (PIMAGE_SECTION_HEADER)(pByte + dos->e_lfanew + sizeof(IMAGE_NT_HEADERS));

                ZeroMemory(&SH[FH->NumberOfSections], sizeof(IMAGE_SECTION_HEADER));

                for (size_t i = 0; i < FH->NumberOfSections; i++, ++SH)
                {
                    // because name is BYTE
                    std::string s(reinterpret_cast<char*>(SH->Name), sizeof(SH->Name));
                    if (s.find(blacklist) != string::npos) {
                        printf("[+] '%s'\t : Section Text(Blacklist)\n", SH->Name);
                    }
                    else {
                        printf("[+] '%s'\t : Section Text\n", SH->Name);
                        RtlCopyMemory(&SH->Name, random_string_only_char(8).c_str(), 8);
                    }
                }

                SetFilePointer(file, SH[FH->NumberOfSections].PointerToRawData + SH[FH->NumberOfSections].SizeOfRawData, NULL, FILE_BEGIN);

                SetEndOfFile(file);

                OH->SizeOfImage = SH[FH->NumberOfSections].VirtualAddress + SH[FH->NumberOfSections].Misc.VirtualSize;

                SetFilePointer(file, 0, NULL, FILE_BEGIN);

                WriteFile(file, pByte, fileSize, &dw, NULL);
                CloseHandle(file);
                printf("\n[+] Success\n");
                std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
                std::cout << "[-] Finished operation in " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "ms" << std::endl;
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